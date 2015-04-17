package com.threadpool;

/**
 * Created by wenyun on 2015-03-19 18:35.
 */

import java.util.concurrent.RejectedExecutionHandler;
import java.util.concurrent.ThreadPoolExecutor;

/**
 * 线程池异常处理类
 */
public class MyRejectedExecutionHandler implements RejectedExecutionHandler {

    @Override
    public void rejectedExecution(Runnable task, ThreadPoolExecutor executor) {

        if (!executor.isShutdown()) {
            System.out.println(" [---- Begin exception handler ----]");
            new Thread(task, "exception by pool").start();
            System.out.println("The pool RejectedExecutionHandler = " + executor.toString());
        }
    }
}