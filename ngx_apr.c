

#include <ngx_http.h>
#include <apr_general.h>
#include <apr.h>

static ngx_int_t ngx_http_apr_preconfiguration(ngx_conf_t *cf);

/*
** handlers for configuration phases of the module
*/

static ngx_http_module_t ngx_http_apr_ctx = {
    ngx_http_apr_preconfiguration, /* preconfiguration */
    NULL, /* postconfiguration */

    NULL, /* create main configuration */
    NULL, /* init main configuration */

    NULL, /* create server configuration */
    NULL, /* merge server configuration */

    NULL, /* create location configuration */
    NULL /* merge location configuration */
};


ngx_module_t ngx_http_apr = {
    NGX_MODULE_V1,
    &ngx_http_apr_ctx, /* module context */
    NULL, /* module directives */
    NGX_HTTP_MODULE, /* module type */
    NULL, /* init master */
    NULL, /* init module */
    NULL, /* init process */
    NULL, /* init thread */
    NULL, /* exit thread */
    NULL, /* exit process */
    NULL, /* exit master */
    NGX_MODULE_V1_PADDING
};

static void ngx_http_apr_terminate(void *dummy) {
    apr_terminate();
}

static ngx_int_t ngx_http_apr_preconfiguration(ngx_conf_t *cf) {
    ngx_pool_cleanup_t *cln;

    apr_initialize();

    cln = ngx_pool_cleanup_add(cf->pool, 0);

    if (cln == NULL) {
        return NGX_ERROR;
    }

    cln->handler = ngx_http_apr_terminate;

    return NGX_OK;
}

