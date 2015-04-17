package com.threadpool;

/**
 * Created by wenyun on 2015-03-19 18:25.
 */

import com.threadpool.Model.ResultModel;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Future;
import java.util.concurrent.ThreadPoolExecutor;

/**
 * 线程池工厂方法
 */
public class ThreadPoolFactory {

    private ThreadPoolExecutor pool;

    private Map<String,ResultContext> resultContextMap;

    /**
     * 私有构造函数
     */
    public ThreadPoolFactory(ThreadPoolConfig config) {
        resultContextMap = new HashMap<String, ResultContext>();
        InitThreadPoolFactory(config);
    }

    public Map<String,ResultContext> getResultContexts() {
        return resultContextMap;
    }

    /**
     * 配置工厂对象
     * @param config
     * @return
     */
    public void InitThreadPoolFactory(ThreadPoolConfig config) {
        if (config.getHandler() == null) {
            pool = new ThreadPoolExecutor(config.getCorePoolSize(),
            config.getMaximumPoolSize(), config.getKeepAliveTime(),
            config.getUnit(), config.getWorkQueue());
        } else {
            pool = new ThreadPoolExecutor(config.getCorePoolSize(),
            config.getMaximumPoolSize(), config.getKeepAliveTime(),
            config.getUnit(), config.getWorkQueue(), config.getHandler());
        }
    }

    /**
     * 添加线程池任务
     *
     * @param threadTask
     */
    public synchronized void AddOneTask(ThreadTask threadTask) {
        //pool.execute(run);
        Future<ResultModel> future = pool.submit(threadTask);
        ResultContext resultContext = new ResultContext();
        resultContext.setName(threadTask.getThreadName());
        resultContext.setFuture(future);
        resultContextMap.put(threadTask.getThreadName(), resultContext);
    }

    /**
     * 添加线程池任务
     *
     * @param threadTaskList
     */
    public synchronized void AddListTask(List<ThreadTask> threadTaskList) {
        if (threadTaskList != null) {
            for (ThreadTask res : threadTaskList ) {
                this.AddOneTask(res);
            }
        }
    }

    /**
     * 关闭线程池
     */
    public void CleanThreadPool() {
        pool.shutdown();
    }

    public class ResultContext {

        private Future future;

        private String name;

        public void setFuture(Future future) {
            this.future = future;
        }

        public Future getFuture() {
            return future;
        }

        public void setName(String name) {
            this.name = name;
        }

        public String getName() {
            return name;
        }

    }

}