package com.threadpool;

import com.threadpool.Model.ResultModel;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

/**
 * Created by wenyun on 2015-04-17 10:45.
 */
public class ServerModule {

    private Selector selector;

    private Integer port;

    private Integer buffSize = 30;

    ThreadPoolFactory factory;

    public ServerModule(Integer port, ThreadPoolConfig configBean) {
        this.port = port;
        this.factory = new ThreadPoolFactory(configBean);
    }

    public void InitServerConfig() throws IOException {

        ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();
        serverSocketChannel.configureBlocking(false);
        serverSocketChannel.socket().bind(new InetSocketAddress(this.port));
        this.selector = Selector.open();
        serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);

    }

    @SuppressWarnings("unchecked")
    public void SocketEventModule() throws IOException {
        Boolean runFlag = true;
        ByteBuffer buffer = ByteBuffer.allocate(buffSize);
        System.out.println("Server Module Start !");
        while (runFlag) {
            Integer eventSize = selector.select();
            if (eventSize == 0) {
                continue;
            }
            Set selectedKeys = selector.selectedKeys();
            Iterator keyIteator = selectedKeys.iterator();
            while (keyIteator.hasNext()) {
                SelectionKey key = (SelectionKey) keyIteator.next();
                if (key.isAcceptable()) {

                    ServerSocketChannel clientChannal = (ServerSocketChannel) key.channel();
                    SocketChannel channel = clientChannal.accept();
                    channel.configureBlocking(false);//set as non-blocking sockfd
                    channel.socket().setReuseAddress(true);
                    String retMsg = "hiya back, Stranger !";
                    channel.write(ByteBuffer.wrap(retMsg.getBytes()));
                    channel.register(selector, SelectionKey.OP_READ);

                } else if (key.isReadable()) {
                    readEventCallBack(key, buffer);
                } else if (key.isWritable()) {
                    writeEventCallBack(key);
                } else if (key.isValid()) {
                    System.out.println("Something wrong happend !");
                    runFlag = false;
                    keyIteator.remove();
                }
                keyIteator.remove();
            }
        }
        factory.CleanThreadPool();
        selector.close();
    }

    public void writeEventCallBack(SelectionKey key) throws IOException {

        SocketChannel channel = (SocketChannel) key.channel();
        /**
         * TODO:
         * 如果result的buffSize大于设定的bufferSize要考虑循环读取buffer发送，或者建立缓存Buffer区
         * 通过缓存buffer区存起来，然后异步将数据发送到对应的channel
         */
        Map<String, ThreadPoolFactory.ResultContext> resultContexts = factory.getResultContexts();
        ThreadPoolFactory.ResultContext itemContext = resultContexts.get(channel.toString());
        Future<ResultModel> future = itemContext.getFuture();
        ResultModel resultModel = null;
        try {
            resultModel = future.get(1000L, TimeUnit.MILLISECONDS);
        } catch (Throwable e) {
            StringBuilder errMsg = new StringBuilder();
            errMsg.append("FutureTask is interrupted! ");
            future.cancel(true);
        }
        if (resultModel != null) {
            Map<String, Object> more = resultModel.getMore();
            StringBuilder retMsg = new StringBuilder();
            retMsg.append((String) more.get("saltResult"));
            channel.write(ByteBuffer.wrap(retMsg.toString().getBytes()));
            channel.register(selector, SelectionKey.OP_READ);

        }

}

    public void readEventCallBack(SelectionKey key, ByteBuffer buffer) throws IOException {

        SocketChannel channel = (SocketChannel) key.channel();
        channel.read(buffer);
        byte[] data = buffer.array();
        String msg = new String(data).trim();
        if (msg.equals("start")) {
            /**
             *channel 对应原始的socketfd，是天然的客户端区分标识
             */
            String actionType = "food";
            ThreadTask task = new ThreadTask(channel.toString(), 0, actionType);
            this.factory.AddOneTask(task);
            channel.register(selector, SelectionKey.OP_WRITE);
        } else if (msg.equals("close")) {
            channel.close();
        }
        System.out.println("client " + channel.toString() + " send ：" + msg);
        buffer.clear();
    }

}
