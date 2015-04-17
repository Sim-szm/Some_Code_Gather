package com.test;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.Iterator;

/**
 * Created by wenyun on 2015-04-17 11:48.
 */
public class ClientModule {

    private Selector selector;

    private static final String IP = "127.0.0.1";

    private static final Integer PORT = 9527;

    private Integer buffSize = 4096;

    public void InitClientConfig() throws IOException {

        SocketChannel socketChannel = SocketChannel.open();
        socketChannel.configureBlocking(false);
        this.selector = Selector.open();
        socketChannel.connect(new InetSocketAddress(IP, PORT));
        socketChannel.register(selector, SelectionKey.OP_CONNECT);
    }

    public void SocketEventModule() throws IOException{
        Boolean doFlag = true;
        ByteBuffer buffer = ByteBuffer.allocate(buffSize);
        while(doFlag){
            Integer eventSize = selector.select(5000);
            if (eventSize == 0) {
                continue;
            }
            Iterator ite = this.selector.selectedKeys().iterator();
            while(ite.hasNext()) {
                SelectionKey key = (SelectionKey) ite.next();
                if (key.isConnectable()) {
                    SocketChannel channel = (SocketChannel) key.channel();
                    if (channel.isConnectionPending()) {
                        channel.finishConnect();
                    }
                    channel.configureBlocking(false);
                    channel.read(buffer);
                    byte[] data = buffer.array();
                    String msg = new String(data).trim();
                    System.out.println("server says ：" + msg);
                    channel.register(selector,SelectionKey.OP_WRITE);
                    buffer.clear();
                }else if (key.isWritable()) {
                    SocketChannel channel = (SocketChannel) key.channel();
                    System.out.println("user_command: ");
                    BufferedReader inputBuffer = new BufferedReader(new InputStreamReader(System.in));
                    String data = inputBuffer.readLine();
                    if (data.equals("start")) {
                        channel.write(ByteBuffer.wrap(data.getBytes()));
                        channel.register(selector,SelectionKey.OP_READ);
                    }else if (data.equals("exit")){
                        doFlag = false;
                        channel.write(ByteBuffer.wrap("close".getBytes()));
                        channel.close();
                        break;
                    }
                }else if (key.isReadable()) {
                    SocketChannel channel = (SocketChannel) key.channel();
                    channel.read(buffer);
                    byte[] data = buffer.array();
                    String msg = new String(data).trim();
                    System.out.println("server retMsg ：" + msg);
                    channel.register(selector,SelectionKey.OP_WRITE);
                    buffer.clear();
                }
                ite.remove();
            }
        }
        System.out.println("ClientModule Exit !");
    }

    public static void main(String[] args) {
        ClientModule clientModule = new ClientModule();
        try {
            clientModule.InitClientConfig();
            clientModule.SocketEventModule();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}
