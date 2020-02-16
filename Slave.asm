;/*------------------------------------------------------------------*/
;/* --- STC MCU International Limited -------------------------------*/
;/* --- STC 1T Series MCU Simulate I2C Slave Demo -------------------*/
;/* --- Mobile: (86)13922805190 -------------------------------------*/
;/* --- Fax: 86-755-82944243 ----------------------------------------*/
;/* --- Tel: 86-755-82948412 ----------------------------------------*/
;/* --- Web: www.STCMCU.com -----------------------------------------*/
;/* If you want to use the program or the program referenced in the  */
;/* article, please specify in which data and procedures from STC    */
;/*------------------------------------------------------------------*/

SCL BIT P1.0
SDA BIT P1.1

;----------------------------

	ORG 0

RESET:
    SETB SCL
    SETB SDA
    
    CALL I2C_WAITSTART  ;等待起始信号
    CALL I2C_RXBYTE     ;接收地址数据
    CLR C
    CALL I2C_TXACK      ;回应ACK
    SETB C              ;读/写 IDATA[80H - FFH]
    RRC A               ;读/写位->C
    MOV R0,A            ;地址送入R0
    JC READDATA         ;C=1(读) C=0(写)
WRITEDATA:
    CALL I2C_RXBYTE     ;接收数据
    MOV @R0,A           ;写入IDATA
    INC R0              ;地址+1
    CLR C
    CALL I2C_TXACK      ;回应ACK
    CALL I2C_WAITSTOP   ;等待停止信号
    JMP RESET
    
READDATA:
    MOV A,@R0
    INC R0
    CALL I2C_TXBYTE     ;发送IDATA数据
    CALL I2C_RXACK      ;接收ACK
    CALL I2C_WAITSTOP   ;等待停止信号
    JMP RESET





;----------------------------
;等待起始信号
;----------------------------
I2C_WAITSTART:
    JNB SCL,$       ;等待时钟->高
    JB SDA,$        ;等待数据线下降沿
    JB SCL,$        ;等待时钟->低
    RET

;----------------------------
;等待结束信号
;----------------------------
I2C_WAITSTOP:
    JNB SCL,$       ;等待时钟->高
    JNB SDA,$       ;等待数据线上升沿
    RET

;----------------------------
;发送ACK/NAK信号
;----------------------------
I2C_TXACK:
    MOV SDA,C       ;送ACK数据
    JNB SCL,$       ;等待时钟->高
    JB SCL,$        ;等待时钟->低
    SETB SDA        ;发送完成
    RET

;----------------------------
;接收ACK/NAK信号
;----------------------------
I2C_RXACK:
    SETB SDA        ;准备读数据
    JNB SCL,$       ;等待时钟->高
    MOV C,SDA       ;读取ACK信号
    JB SCL,$        ;等待时钟->低
    RET

;----------------------------
;接收一字节数据
;----------------------------
I2C_RXBYTE:
    MOV R7,#8       ;8位计数
RXNEXT:
    JNB SCL,$       ;等待时钟->高
    MOV C,SDA       ;读取数据口
    RLC A           ;保存数据
    JB SCL,$        ;等待时钟->低
    DJNZ R7,RXNEXT  ;收下一位
    RET

;----------------------------
;发送一字节数据
;----------------------------
I2C_TXBYTE:
    MOV R7,#8       ;8位计数
TXNEXT:
    RLC A           ;移出数据位
    MOV SDA,C       ;数据送数据口
    JNB SCL,$       ;等待时钟->高
    JB SCL,$        ;等待时钟->低
    DJNZ R7,TXNEXT  ;送下一位
    RET

;----------------------------

	END
