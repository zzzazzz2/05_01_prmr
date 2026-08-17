#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev != MG_EV_HTTP_MSG) {
    return;
  }

  struct mg_http_message *hm = (struct mg_http_message *) ev_data;

  if (mg_http_match_uri(hm, "/static/#")) {
    struct mg_http_serve_opts opts;
    memset(&opts, 0, sizeof(opts));

    opts.root_dir = ".";

    mg_http_serve_dir(c, hm, &opts);
    return;
  }

  mg_http_reply(c, 200, "", "%s\n", "It works!");
}

int main(void) {
  struct mg_mgr mgr;
  mg_mgr_init(&mgr);
  mg_http_listen(&mgr, "http://0.0.0.0:8888", fn, &mgr);
  for (;;) {
    mg_mgr_poll(&mgr, 1000);
  }
  mg_mgr_free(&mgr);
  return EXIT_SUCCESS;
}

