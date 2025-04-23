#This program is for learning only,Not to be used for any other purpose
#without the permission of the author
#Testing Hardware:Raspberry PI all series
#QDtech-LCD liquid crystal driver for Raspberry PI
#xiaofeng@ShenZhen QDtech co.,LTD
#Company Website:www.qdtft.com
#Taobao Website:http://qdtech.taobao.com
#wiki Technology Website:http://www.lcdwiki.com
#We provide technical support,Any technical questions are welcome to
#exchange and study at any time
#Fixed telephone (fax):+86 0755-23594567
#cell-phone:15989313508(Mr Feng)
#E-mail:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
#Technical Support QQ:3002773612  3002778157
#Technical Exchange QQ group:324828016
#Date:2021/4/6
#Version:V1.0
#Copyright reserved, piracy must be investigated
#Copyright(C) ShenZhen QDtech co.,LTD 2018-2028
#All rights reserved
#****************************************************************************************************
#This program uses the bcm2835 gpio library,
#so the pin definition using BCM coding
#This is python program
#=====================================power supply wiring===========================================//
# OLED Module                Raspberry PI
#    VCC        connect       DC 5V/3.3V      //LCD power positive, Physical pin 1,17
#    GND        connect          GND          //LCD power ground,Physical pin 6,9,14,20,25,30,34,39
#======================================data line wiring=============================================//
#The default data bus type for this module is 4-wire SPI
# OLED Module                Raspberry PI
#    SDA        connect       19(bcm:10)      //LCD spi write signal
#======================================control line wiring==========================================//
# OLED Module                Raspberry PI
#    RES        connect        5(bcm:3)       //LCD reset control signal
#    DC         connect        3(bcm:2)       //LCD data or command selection control signal
#    SCL        connect       23(bcm:11)      //LCD spi colck signal
#    CS         connect        8(bcm:24)      //LCD cs control signal low active
#    BLK        connect       12(bcm:18)      //LCD backlight control signal, if no control is needed, connect to 3.3V
#========================================touch screen wiring========================================//
#This module has no touch function,so it don't need touch screen wiring
#*****************************************************************************************************/
#/****************************************************************************************************
#  * @attention
#  *
#  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
#  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
#  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
#  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
#  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
#  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
#*****************************************************************************************************/

# -*- coding: UTF-8 -*-
import lcd
import time
import os

from lcd import USE_HORIZONTAL

from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont

CS = 8
DC =  2
RES = 3
BLK = 18

ColorTab=['RED','GREEN','BLUE','YELLOW','BROWN']
Direction=['Rotation:0','Rotation:90','Rotation:180','Rotation:270']

curpath = os.getcwd()
font1 = curpath+"/../font/simsun.ttc"

pic1 = curpath+"/../pic/pic-1.jpg"
pic2 = curpath+"/../pic/pic-2.jpg"
pic3 = curpath+"/../pic/pic-3.jpg"
pic4 = curpath+"/../pic/pic-4.jpg"
pic5 = curpath+"/../pic/pic-5.jpg"

mylcd = lcd.ST7789H2(RES,DC,CS,BLK)
mylcd.lcdinit()

while 1:
    lcdimage = Image.new("RGB", (mylcd.width, mylcd.height),"WHITE")
    display = ImageDraw.Draw(lcdimage)
    lcdfont = ImageFont.truetype(font1,16)
    display.rectangle((0,0,mylcd.width,32),fill="BLUE")
    display.rectangle((0,mylcd.height-32,mylcd.width,mylcd.height),fill="BLUE")
    display.text((71,12),"test program", font=lcdfont,fill="WHITE")
    display.text((59,mylcd.height-32),"www.lcdwiki.com", font=lcdfont,fill="WHITE")
    display.text((51,73),"QDTECH Electronic", font=lcdfont,fill="RED")
    display.text((55,90),"LCD test program", font=lcdfont,fill="RED")
    display.text((51,107),"0.96inch ST7789H2", font=lcdfont,fill="GREEN")
    display.text((91,124),"240x198", font=lcdfont,fill="GREEN")
    display.text((79,141),"2023-09-22", font=lcdfont,fill="BLUE")
    mylcd.lcdimage(lcdimage)
    time.sleep(1.5)

    display.rectangle((0,0,mylcd.width,mylcd.height),fill="WHITE")
    display.text((40,30),"WHITE", font=lcdfont,fill="BLACK")
    mylcd.lcdimage(lcdimage)
    time.sleep(1)
    display.rectangle((0,0,mylcd.width,mylcd.height),fill=0)
    display.text((40,30),"BLACK", font=lcdfont,fill="WHITE")
    mylcd.lcdimage(lcdimage)
    time.sleep(1)
    display.rectangle((0,0,mylcd.width,mylcd.height),fill="RED")
    display.text((40,30),"RED", font=lcdfont,fill="BLUE")
    mylcd.lcdimage(lcdimage)
    time.sleep(1)
    display.rectangle((0,0,mylcd.width,mylcd.height),fill="GREEN")
    display.text((40,30),"GREEN", font=lcdfont,fill="BLUE")
    mylcd.lcdimage(lcdimage)
    time.sleep(1)
    display.rectangle((0,0,mylcd.width,mylcd.height),fill="BLUE")
    display.text((40,30),"BLUE", font=lcdfont,fill="RED")
    mylcd.lcdimage(lcdimage)
    time.sleep(1)

    display.rectangle((0,0,mylcd.width,mylcd.height),fill="WHITE")
    display.rectangle((0,0,mylcd.width,32),fill="BLUE")
    display.rectangle((0,mylcd.height-32,mylcd.width,mylcd.height),fill="BLUE")
    display.text((63,12),"Rectangle Fill", font=lcdfont,fill="WHITE")
    display.text((59,mylcd.height-32),"www.lcdwiki.com", font=lcdfont,fill="WHITE")
    for i in range(5):
        display.rectangle((mylcd.width/2-40+(i*16),mylcd.height/2-40+(i*13),mylcd.width/2-40+(i*16)+30,mylcd.height/2-40+(i*13)+30),outline=ColorTab[i])
    mylcd.lcdimage(lcdimage)
    time.sleep(1)
    for i in range(5):
        display.rectangle((mylcd.width/2-40+(i*16),mylcd.height/2-40+(i*13),mylcd.width/2-40+(i*16)+30,mylcd.height/2-40+(i*13)+30),fill=ColorTab[i])
    mylcd.lcdimage(lcdimage)
    time.sleep(1)


    display.rectangle((0,0,mylcd.width,mylcd.height),fill="WHITE")
    display.rectangle((0,0,mylcd.width,32),fill="BLUE")
    display.rectangle((0,mylcd.height-32,mylcd.width,mylcd.height),fill="BLUE")
    display.text((75,12),"Circle Fill", font=lcdfont,fill="WHITE")
    display.text((59,mylcd.height-32),"www.lcdwiki.com", font=lcdfont,fill="WHITE")
    for i in range(5):
        display.ellipse((mylcd.width/2-55+(i*15),mylcd.height/2-40+(i*13),mylcd.width/2-25+(i*15),mylcd.height/2-10+(i*13)),outline=ColorTab[i])
    mylcd.lcdimage(lcdimage)
    time.sleep(1)
    for i in range(5):
        display.ellipse((mylcd.width/2-55+(i*15),mylcd.height/2-40+(i*13),mylcd.width/2-25+(i*15),mylcd.height/2-10+(i*13)),fill=ColorTab[i])
    mylcd.lcdimage(lcdimage)
    time.sleep(1)

    display.rectangle((0,0,mylcd.width,mylcd.height),fill="WHITE")
    display.rectangle((0,0,mylcd.width,32),fill="BLUE")
    display.rectangle((0,mylcd.height-32,mylcd.width,mylcd.height),fill="BLUE")
    display.text((67,12),"Triangle Fill", font=lcdfont,fill="WHITE")
    display.text((59,mylcd.height-32),"www.lcdwiki.com", font=lcdfont,fill="WHITE")
    for i in range(5):
        display.polygon([(mylcd.width/2-40+(i*15),mylcd.height/2-12+(i*11)),(mylcd.width/2-25-1+(i*15),mylcd.height/2-12-26-1+(i*11)),(mylcd.width/2-10-1+(i*15),mylcd.height/2-12+(i*11))],outline=ColorTab[i])
    mylcd.lcdimage(lcdimage)
    time.sleep(1)
    for i in range(5):
        display.polygon([(mylcd.width/2-40+(i*15),mylcd.height/2-12+(i*11)),(mylcd.width/2-25-1+(i*15),mylcd.height/2-12-26-1+(i*11)),(mylcd.width/2-10-1+(i*15),mylcd.height/2-12+(i*11))],fill=ColorTab[i])
    mylcd.lcdimage(lcdimage)
    time.sleep(1)

    display.rectangle((0,0,mylcd.width,mylcd.height),fill="WHITE")
    display.rectangle((0,0,mylcd.width,32),fill="BLUE")
    display.rectangle((0,mylcd.height-32,mylcd.width,mylcd.height),fill="BLUE")
    display.text((71,12),"FONT Display", font=lcdfont,fill="WHITE")
    display.text((59,mylcd.height-32),"www.lcdwiki.com", font=lcdfont,fill="WHITE")
    lcdfont = ImageFont.truetype(font1,12)
    display.text((30,57),"6X12:ABCDEabcde01234567", font=lcdfont,fill="RED")
    lcdfont = ImageFont.truetype(font1,16)
    display.text((30,69),"8X16:abcde01234", font=lcdfont,fill="RED")
    lcdfont = ImageFont.truetype(font1,24)
    display.text((30,85),"12X24:ABCD01234", font=lcdfont,fill="RED")
    lcdfont = ImageFont.truetype(font1,32)
    display.text((30,109),"16X32:@#$%&", font=lcdfont,fill="RED") 
    lcdfont = ImageFont.truetype(font1,48)
    display.text((30,141),"24X48:A", font=lcdfont,fill="RED")
    mylcd.lcdimage(lcdimage)
    time.sleep(1)

    pic = Image.open(pic1)
    mylcd.lcdimage(pic)
    time.sleep(1.5)
    pic = Image.open(pic2)
    mylcd.lcdimage(pic)
    time.sleep(1.5)
    pic = Image.open(pic3)
    mylcd.lcdimage(pic)
    time.sleep(1.5)
    pic = Image.open(pic4)
    mylcd.lcdimage(pic)
    time.sleep(1.5)
    pic = Image.open(pic5)
    mylcd.lcdimage(pic)
    time.sleep(1.5)

    lcdfont = ImageFont.truetype(font1,16)
    for i in range(2):
        mylcd.lcddirection(i)
        pic = Image.open(pic2)
        display = ImageDraw.Draw(pic)
        display.rectangle((0,0,mylcd.width,32),fill="BLUE")
        display.rectangle((0,mylcd.height-32,mylcd.width,mylcd.height),fill="BLUE")
        display.text((55,12),"Rotation Display", font=lcdfont,fill="WHITE") 
        display.text((59,mylcd.height-32),"www.lcdwiki.com", font=lcdfont,fill="WHITE")
        display.text((40,35),Direction[i], font=lcdfont,fill="RED")
        mylcd.lcdimage(pic)
        time.sleep(1)

    mylcd.lcddirection(USE_HORIZONTAL)
