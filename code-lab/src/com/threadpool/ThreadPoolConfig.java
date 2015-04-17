package com.threadpool;

/**
 * Created by wenyun on 2015-03-19 18:30.
 */

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.RejectedExecutionHandler;
import java.util.concurrent.TimeUnit;

/**
 * 线程池配置类
 */
public class ThreadPoolConfig {

    private Integer corePoolSize;

    private Integer maxnumPoolSize;

    private Long keepAliveTime;

    private TimeUnit unit;

    private BlockingQueue<Runnable> workQueue;

    private RejectedExecutionHandler handler;

    private static ThreadPoolConfig config;
    /**
     * 单例模式
     */
    private ThreadPoolConfig(){

    }

    /**
     * 获取配置文件对象
     * @return
     */
    public static ThreadPoolConfig getInstance(){
        if(config == null){
            config = new ThreadPoolConfig();
        }
        return config;
    }

    public int getCorePoolSize() {
        return corePoolSize;
    }

    public void setCorePoolSize(int corePoolSize) {
        this.corePoolSize = corePoolSize;
    }

    public int getMaximumPoolSize() {
        return maxnumPoolSize;
    }

    public void setMaximumPoolSize(int maximumPoolSize) {
        this.maxnumPoolSize = maximumPoolSize;
    }

    public long getKeepAliveTime() {
        return keepAliveTime;
    }

    public void setKeepAliveTime(long keepAliveTime) {
        this.keepAliveTime = keepAliveTime;
    }

    public TimeUnit getUnit() {
        return unit;
    }

    public void setUnit(TimeUnit unit) {
        this.unit = unit;
    }

    public BlockingQueue<Runnable> getWorkQueue() {
        return workQueue;
    }

    public void setWorkQueue(BlockingQueue<Runnable> workQueue) {
        this.workQueue = workQueue;
    }

    public RejectedExecutionHandler getHandler() {
        return handler;
    }

    public void setHandler(RejectedExecutionHandler handler) {
        this.handler = handler;
    }
}