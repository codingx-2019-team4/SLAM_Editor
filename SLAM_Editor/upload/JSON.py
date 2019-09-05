#!/usr/bin/env python
# coding: utf-8

# In[8]:


#!/usr/bin/python
# -*- coding: UTF-8 -*-

import sys
import socket# 客户端 发送一个数据，再接收一个数据
import time
client = socket.socket(socket.AF_INET,socket.SOCK_STREAM) #声明socket类型，同时生成链接对象
ip = "140.116.182.200"
port = 6668

client.connect((ip,port)) #建立一个链接，连接到本地的6969端口

# 傳json檔
jsonFile = open(sys.argv[1], "rb")
txt = "json"
client.send(txt.encode('utf-8'))
time.sleep(5)
while True:
    jsonData = jsonFile.read(1)
    if not jsonData:
        break  # 讀完檔案結束迴圈
    client.send(jsonData)
client.close() #关闭这个链接

