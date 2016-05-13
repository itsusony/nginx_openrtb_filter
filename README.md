# nginx_openrtb_filter
a filter of openrtb's biddings. it will add result flag into request header.

- done:
  - set header openrtb=ok when uri contains the keyword of openrtb
  - sample uri: http://127.0.0.1/?openrtb=1

- todo:
  - precheck request POST body to confirm the openrtb format.
  - add the extension of custom logic
  - add cache connection to exchange data directly.

- how to install?
  - under nginx source.
  - ```./configure --add-module=/PATH_TO_MODULE; make; make install```

- contact me
  - meng.xiangliang1985@gmail.com
