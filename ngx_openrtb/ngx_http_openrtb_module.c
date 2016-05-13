
/*
 * Copyright (C) Xiangliang Meng.
 * Copyright (C) Freakout.
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_string.h>

static ngx_http_module_t ngx_http_openrtb_module_ctx = {
    NULL,  /* preconfiguration */
    NULL,  /* postconfiguration */

    NULL,  /* create main configuration */
    NULL,  /* init main configuration */

    NULL,  /* create server configuration */
    NULL,  /* merge server configuration */

    NULL,  /* create location configuration */
    NULL
};

static ngx_int_t ngx_http_openrtb_handler(ngx_http_request_t *r){
    if (r->uri_changes == 11){ // redirect will let header be setted twice. nginx redirect max 11 times.
        ngx_log_error(NGX_LOG_DEBUG, r->connection->log, 0, "debug start. fmt supported here");
        if (r->unparsed_uri.len > 7 && ngx_strstr(r->unparsed_uri.data,"openrtb")){
            ngx_table_elt_t *h = ngx_list_push(&r->headers_out.headers);
            if (h==NULL)return NGX_ERROR;
            ngx_str_t key = ngx_string("openrtb");
            ngx_str_t val = ngx_string("ok");
            h->key = key;
            h->value = val;
            h->hash = 1;
        }
    }
    return NGX_DECLINED;
}

static char* ngx_http_openrtb(ngx_conf_t *cf, ngx_command_t *cmd, void *conf){
    ngx_http_core_loc_conf_t *clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_openrtb_handler;
    return NGX_CONF_OK;
}

static ngx_command_t  ngx_http_openrtb_commands[] = {
    { ngx_string("openrtb"),
      NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
      ngx_http_openrtb,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL },
      ngx_null_command
};

ngx_module_t ngx_http_openrtb_module = {
    NGX_MODULE_V1,
    &ngx_http_openrtb_module_ctx,
    ngx_http_openrtb_commands,
    NGX_HTTP_MODULE,
    NULL,                                  /* init master */
    NULL,                                  /* init module */
    NULL,                                  /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING
};
