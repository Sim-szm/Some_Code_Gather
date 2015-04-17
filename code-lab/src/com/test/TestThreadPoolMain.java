package com.test;

/**
 * Created by wenyun on 2015-03-19 18:25.
 */

import com.threadpool.MyRejectedExecutionHandler;
import com.threadpool.ServerModule;
import com.threadpool.ThreadPoolConfig;

import java.io.IOException;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.TimeUnit;

public class TestThreadPoolMain {

    private  static Integer coreNum = 2;
    private static Integer maxNum = 4;
    private static long keepAlive = 60L;
    private static Integer queueLength = 5;
    private static final Long TIMEOUT = 1000L;
    private static final String keyType = "food";

    private static final Integer port = 9527;

    public static void main(String[] args) {

        ThreadPoolConfig configBean = ThreadPoolConfig.getInstance();
        configBean.setCorePoolSize(coreNum);
        configBean.setMaximumPoolSize(maxNum);
        configBean.setKeepAliveTime(keepAlive);
        configBean.setUnit(TimeUnit.SECONDS);
        try {
            configBean.setWorkQueue(new ArrayBlockingQueue<Runnable>(queueLength));
        } catch (Exception e) {
            e.printStackTrace();
        }
        configBean.setHandler(new MyRejectedExecutionHandler());

        ServerModule serverModule = new ServerModule(9527, configBean);
        try {
            serverModule.InitServerConfig();
            serverModule.SocketEventModule();
        } catch (IOException e) {
            e.printStackTrace();
        }finally {
            System.out.println("never-fucking-touch-area");
        }

    }

}
