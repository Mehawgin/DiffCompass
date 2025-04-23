#ifndef HTML_H
#define HTML_H
//####################################################################################################
//网页显示HTML
//####################################################################################################
const char mainPageString[] PROGMEM = "<!DOCTYPE html>\r\n\
<html>\r\n\
<head>\r\n\
  <meta http-equiv='Content-type' content='text/html; charset=utf-8'>\r\n\
  <title>ESP Monitor</title>\r\n\
</head>\r\n\
<body>\r\n\
  <center>\r\n\
  </br>\r\n\
  </br>\r\n\
  </br>\r\n\
  </br>\r\n\
  </br>\r\n\
  </br>\r\n\
  </br>\r\n\
  </br>\r\n\
  <form method='POST' action='/' enctype='multipart/form-data'>\r\n\
  <input type='file' name='update' id='update'><input type='submit' value='提交'></form>\r\n\
  <p>文件格式必须为jpg格式，当前屏幕为2.8寸TFT,分辨率240*320</p>\r\n\
  <form action='/LED-Control'>\r\n\
    设置图片播放数<input type='text' name='value1'>\r\n\
    </br>\r\n\
    </br>\r\n\
    设置延时时间<input type='text' name='value2'>\r\n\
    </br>\r\n\
    </br>\r\n\
    <input type='submit' value='保存'>\r\n\
  </form>\r\n\
</body></center>\r\n\
</html>";
//####################################################################################################
// 上传完成后的网页文件
//####################################################################################################
const char uploadString[] PROGMEM = "<!DOCTYPE html>\r\n\
<html>\r\n\
<head>\r\n\
  <meta http-equiv='Content-type' content='text/html; charset=utf-8'>\r\n\
  <title>ESP32 上传完成</title>\r\n\
</head>\r\n\
<body>\r\n\
  </br>\r\n\
  </br>\r\n\
  <center><img src='/logo.bmp' width='128' height='128' />\r\n\
  <form method='POST' action='/' enctype='multipart/form-data'>\r\n\
  <p>上传完成</p>\r\n\
  </br>\r\n\
  </br>\r\n\
</body></center>\r\n\
</html>";
#endif
