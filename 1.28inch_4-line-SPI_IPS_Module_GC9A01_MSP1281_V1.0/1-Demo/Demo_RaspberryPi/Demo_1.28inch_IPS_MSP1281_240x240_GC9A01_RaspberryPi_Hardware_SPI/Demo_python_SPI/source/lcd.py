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
#    VCC        connect       DC 3.3V         //OLED power positive, Physical pin 1,17
#    GND        connect          GND          //OLED power ground,Physical pin 6,9,14,20,25,30,34,39
#======================================data line wiring=============================================//
#The default data bus type for this module is 4-wire SPI
# OLED Module                Raspberry PI
#    SDA        connect       19(bcm:10)      //OLED spi write signal
#======================================control line wiring==========================================//
# OLED Module                Raspberry PI
#    RES        connect        5(bcm:3)       //OLED reset control signal
#    DC         connect        3(bcm:2)       //OLED data or command selection control signal
#    SCL        connect       23(bcm:11)      //OLED spi colck signal
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
import lcd_spi
import RPi.GPIO as GPIO
import time
import numpy as np

"""Define the size of the LCD"""
LCD_W = 240
LCD_H = 240

USE_HORIZONTAL=0 #Define the clockwise rotation direction of LCD screen:
                 #// 0-0 degree rotation, 1-90 degree rotation, 2-180 degree rotation, 3-270 degree rotation

# Initialize spi
myspi = lcd_spi.lcdspi()

class GC9A01(object):
    """class for GC9A01 240*240 1.28inch IPS SPI round LCD module."""
    def __init__(self,res,dc,cs,blk):
        # set lcd display parameter
        self.width = 0 #LCD width
        self.height = 0 #LCD height
        self.lcdid = 0  #LCD ID
        self.lcddir = 0 #LCD display direction
        self.wramcmd = 0x2C #Start writing gram instruction
        self.setxcmd = 0x2A #Set X coordinate command
        self.setycmd = 0x2B #Set Y coordinate command
        self.setdircmd = 0x36 #Set lcd display direction command
        # Initialize oled pin
        self.lcdled = blk
        self.lcdrs = dc
        self.lcdrst = res
        self.lcdcs = cs
    def lcdledset(self):
        GPIO.output(self.lcdled,GPIO.HIGH)
    def lcdledclr(self):
        GPIO.output(self.lcdled,GPIO.LOW)
    def lcdrsset(self):
        GPIO.output(self.lcdrs,GPIO.HIGH)
    def lcdrsclr(self):
        GPIO.output(self.lcdrs,GPIO.LOW)
    def lcdrstset(self):
        GPIO.output(self.lcdrst,GPIO.HIGH)
    def lcdrstclr(self):
        GPIO.output(self.lcdrst,GPIO.LOW)
    def lcdcsset(self):
        GPIO.output(self.lcdcs,GPIO.HIGH)
    def lcdcsclr(self):
        GPIO.output(self.lcdcs,GPIO.LOW)
    def lcdwrreg(self,value):
        self.lcdcsclr()
        self.lcdrsclr()
        myspi.spiwritebyte(value)
        self.lcdcsset()
    def lcdwrdata(self,value):
        self.lcdcsclr()
        self.lcdrsset()
        myspi.spiwritebyte(value)
        self.lcdcsset()
    def lcdwritereg(self,reg,value):
        self.lcdwrreg(reg)
        self.lcdwrdata(value)
    def lcdwriteram(self):
        self.lcdwrreg(self.wramcmd)
    def lcdwrite16bitdata(self,value):
        self.lcdcsclr()
        self.lcdrsset()
        myspi.spiwritebyte(value>>8)
        myspi.spiwritebyte(value)
        self.lcdcsset()
    def lcdsetwindows(self,xstart,ystart,xend,yend):
        self.lcdwrreg(self.setxcmd)
        self.lcdwrdata(xstart>>8)
        self.lcdwrdata(xstart)
        self.lcdwrdata(xend>>8)
        self.lcdwrdata(xend)
        self.lcdwrreg(self.setycmd)
        self.lcdwrdata(ystart>>8)
        self.lcdwrdata(ystart)
        self.lcdwrdata(yend>>8)
        self.lcdwrdata(yend)
        self.lcdwriteram()
    def lcdsetcursor(self,xpos,ypos):
        self.lcdsetwindows(xpos,ypos,xpos,ypos)
    def lcddrawpoint(self,x,y,color):
        self.lcdsetcursor(x,y)
        self.lcdwrite16bitdata(color)
    def lcdclear(self,color):
        self.lcdsetwindows(0,0,self.width-1,self.height-1)
        self.lcdcsclr()
        self.lcdrsset()
        for i in range(0,self.height):
            for m in range(0,self.width):
                myspi.spiwritebyte(color>>8)
                myspi.spiwritebyte(color)
        self.lcdcsset()
    def lcdgpioinit(self):
        GPIO.setmode(GPIO.BCM)
        GPIO.setwarnings(False)
        GPIO.setup(self.lcdled,GPIO.OUT)
        GPIO.setup(self.lcdrs,GPIO.OUT)
        GPIO.setup(self.lcdrst,GPIO.OUT)
        GPIO.setup(self.lcdcs,GPIO.OUT)
    def lcdreset(self):
        self.lcdrstclr()
        time.sleep(0.02)
        self.lcdrstset()
        time.sleep(0.02)
    def lcddirection(self,value):
        if value == 0:
            self.width = LCD_W
            self.height = LCD_H
            self.lcdwritereg(self.setdircmd,(1<<3))
        elif value == 1:
            self.width = LCD_H
            self.height = LCD_W
            self.lcdwritereg(self.setdircmd,(1 << 6)|(1 << 5)|(1<<3))
        elif value == 2:
            self.width = LCD_W
            self.height = LCD_H
            self.lcdwritereg(self.setdircmd,(1 << 6)|(1 << 7)|(1<<3))
        elif value == 3:
            self.width = LCD_H
            self.height = LCD_W
            self.lcdwritereg(self.setdircmd,(1 << 5)|(1 << 7)|(1<<3))
        else:
            raise ValueError('direction value must be 0~3')
    def lcdinit(self):
        self.lcdgpioinit() #LCD GPIO initialization
        self.lcdreset()    #LCD reset
        """init GC9A01"""
        self.lcdwrreg(0xEF);
        self.lcdwrreg(0xEB);
        self.lcdwrdata(0x14);
        self.lcdwrreg(0xFE);
        self.lcdwrreg(0xEF);
        self.lcdwrreg(0xEB);
        self.lcdwrdata(0x14);
        self.lcdwrreg(0x84);
        self.lcdwrdata(0x40);
        self.lcdwrreg(0x85);
        self.lcdwrdata(0xFF);
        self.lcdwrreg(0x86);
        self.lcdwrdata(0xFF);
        self.lcdwrreg(0x87);
        self.lcdwrdata(0xFF);
        self.lcdwrreg(0x88);
        self.lcdwrdata(0x0A);
        self.lcdwrreg(0x89);
        self.lcdwrdata(0x21);
        self.lcdwrreg(0x8A);
        self.lcdwrdata(0x00);
        self.lcdwrreg(0x8B);
        self.lcdwrdata(0x80);
        self.lcdwrreg(0x8C);
        self.lcdwrdata(0x01);
        self.lcdwrreg(0x8D);
        self.lcdwrdata(0x01);
        self.lcdwrreg(0x8E);
        self.lcdwrdata(0xFF);
        self.lcdwrreg(0x8F);
        self.lcdwrdata(0xFF);
        self.lcdwrreg(0xB6);
        self.lcdwrdata(0x00);
        self.lcdwrdata(0x20);
        self.lcdwrreg(0x36);
        self.lcdwrdata(0x08);
        self.lcdwrreg(0x3A);
        self.lcdwrdata(0x05);
        self.lcdwrreg(0x90);
        self.lcdwrdata(0x08);
        self.lcdwrdata(0x08);
        self.lcdwrdata(0x08);
        self.lcdwrdata(0x08);
        self.lcdwrreg(0xBD);
        self.lcdwrdata(0x06);
        self.lcdwrreg(0xBC);
        self.lcdwrdata(0x00);
        self.lcdwrreg(0xFF);
        self.lcdwrdata(0x60);
        self.lcdwrdata(0x01);
        self.lcdwrdata(0x04);
        self.lcdwrreg(0xC3);
        self.lcdwrdata(0x13);
        self.lcdwrreg(0xC4);
        self.lcdwrdata(0x13);
        self.lcdwrreg(0xC9);
        self.lcdwrdata(0x22);
        self.lcdwrreg(0xBE);
        self.lcdwrdata(0x11);
        self.lcdwrreg(0xE1);
        self.lcdwrdata(0x10);
        self.lcdwrdata(0x0E);
        self.lcdwrreg(0xDF);
        self.lcdwrdata(0x21);
        self.lcdwrdata(0x0c);
        self.lcdwrdata(0x02);
        self.lcdwrreg(0xF0);
        self.lcdwrdata(0x45);
        self.lcdwrdata(0x09);
        self.lcdwrdata(0x08);
        self.lcdwrdata(0x08);
        self.lcdwrdata(0x26);
        self.lcdwrdata(0x2A);
        self.lcdwrreg(0xF1);
        self.lcdwrdata(0x43);
        self.lcdwrdata(0x70);
        self.lcdwrdata(0x72);
        self.lcdwrdata(0x36);
        self.lcdwrdata(0x37);
        self.lcdwrdata(0x6F);
        self.lcdwrreg(0xF2);
        self.lcdwrdata(0x45);
        self.lcdwrdata(0x09);
        self.lcdwrdata(0x08);
        self.lcdwrdata(0x08);
        self.lcdwrdata(0x26);
        self.lcdwrdata(0x2A);
        self.lcdwrreg(0xF3);
        self.lcdwrdata(0x43);
        self.lcdwrdata(0x70);
        self.lcdwrdata(0x72);
        self.lcdwrdata(0x36);
        self.lcdwrdata(0x37);
        self.lcdwrdata(0x6F);
        self.lcdwrreg(0xED);
        self.lcdwrdata(0x1B);
        self.lcdwrdata(0x0B);
        self.lcdwrreg(0xAE);
        self.lcdwrdata(0x77);
        self.lcdwrreg(0xCD);
        self.lcdwrdata(0x63);
        self.lcdwrreg(0x70);
        self.lcdwrdata(0x07);
        self.lcdwrdata(0x07);
        self.lcdwrdata(0x04);
        self.lcdwrdata(0x0E);
        self.lcdwrdata(0x0F);
        self.lcdwrdata(0x09);
        self.lcdwrdata(0x07);
        self.lcdwrdata(0x08);
        self.lcdwrdata(0x03);
        self.lcdwrreg(0xE8);
        self.lcdwrdata(0x34);
        self.lcdwrreg(0x62);
        self.lcdwrdata(0x18);
        self.lcdwrdata(0x0D);
        self.lcdwrdata(0x71);
        self.lcdwrdata(0xED);
        self.lcdwrdata(0x70);
        self.lcdwrdata(0x70);
        self.lcdwrdata(0x18);
        self.lcdwrdata(0x0F);
        self.lcdwrdata(0x71);
        self.lcdwrdata(0xEF);
        self.lcdwrdata(0x70);
        self.lcdwrdata(0x70);
        self.lcdwrreg(0x63);
        self.lcdwrdata(0x18);
        self.lcdwrdata(0x11);
        self.lcdwrdata(0x71);
        self.lcdwrdata(0xF1);
        self.lcdwrdata(0x70);
        self.lcdwrdata(0x70);
        self.lcdwrdata(0x18);
        self.lcdwrdata(0x13);
        self.lcdwrdata(0x71);
        self.lcdwrdata(0xF3);
        self.lcdwrdata(0x70);
        self.lcdwrdata(0x70);
        self.lcdwrreg(0x64);
        self.lcdwrdata(0x28);
        self.lcdwrdata(0x29);
        self.lcdwrdata(0xF1);
        self.lcdwrdata(0x01);
        self.lcdwrdata(0xF1);
        self.lcdwrdata(0x00);
        self.lcdwrdata(0x07);
        self.lcdwrreg(0x66);
        self.lcdwrdata(0x3C);
        self.lcdwrdata(0x00);
        self.lcdwrdata(0xCD);
        self.lcdwrdata(0x67);
        self.lcdwrdata(0x45);
        self.lcdwrdata(0x45);
        self.lcdwrdata(0x10);
        self.lcdwrdata(0x00);
        self.lcdwrdata(0x00);
        self.lcdwrdata(0x00);
        self.lcdwrreg(0x67);
        self.lcdwrdata(0x00);
        self.lcdwrdata(0x3C);
        self.lcdwrdata(0x00);
        self.lcdwrdata(0x00);
        self.lcdwrdata(0x00);
        self.lcdwrdata(0x01);
        self.lcdwrdata(0x54);
        self.lcdwrdata(0x10);
        self.lcdwrdata(0x32);
        self.lcdwrdata(0x98);
        self.lcdwrreg(0x74);
        self.lcdwrdata(0x10);
        self.lcdwrdata(0x85);
        self.lcdwrdata(0x80);
        self.lcdwrdata(0x00);
        self.lcdwrdata(0x00);
        self.lcdwrdata(0x4E);
        self.lcdwrdata(0x00);
        self.lcdwrreg(0x98);
        self.lcdwrdata(0x3e);
        self.lcdwrdata(0x07);
        self.lcdwrreg(0x35);
        self.lcdwrreg(0x21);
        self.lcdwrreg(0x11);
        time.sleep(0.12);
        self.lcdwrreg(0x29);
        time.sleep(0.02)
        self.lcddirection(USE_HORIZONTAL)
        self.lcdledset()
#        self.lcdclear(0xFFFF)
    def lcdimage(self,image):
        """set the value of Python Image Library to lcd GRAM"""
        imgwidth,imgheight = image.size
        if imgwidth != self.width or imgheight != self.height:
            raise ValueError('Image must be same dimensions as display({0}x{1}).' .format(self.width, self.height))
        img = np.asarray(image)
        pix = np.zeros((self.width,self.height,2), dtype = np.uint8)
        pix[...,[0]] = np.add(np.bitwise_and(img[...,[0]],0xF8),np.right_shift(img[...,[1]],5))
        pix[...,[1]] = np.add(np.bitwise_and(np.left_shift(img[...,[1]],3),0xE0),np.right_shift(img[...,[2]],3))
        pix = pix.flatten().tolist()
        self.lcdsetwindows(0,0,imgwidth-1,imgheight-1)
        self.lcdrsset()
        for i in range(0,len(pix),4096):
            myspi.spi.writebytes(pix[i:i+4096])
