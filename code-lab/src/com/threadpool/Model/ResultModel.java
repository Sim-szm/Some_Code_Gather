package com.threadpool.Model;

import java.io.Serializable;
import java.util.Map;

/**
 * Created by wenyun on 2015-04-16 12:32.
 */
public class ResultModel implements Serializable {

    public static final long serialVersionUID = 2L;

    private Integer id;

    private String name;

    private Map<String, Object> more;

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Map<String, Object> getMore() {
        return more;
    }

    public void setMore(Map<String, Object> more) {
        this.more = more;
    }
}
