
#include "Bsp.h"
#include "srio_drv.h"

Uint8 softWareInfo[32];
DAT_FIFO_TYP RS422_RECV_FIFO[RS422_CH_MAX_NUM];
DAT_FIFO_TYP SPI_RECV_FIFO[SPI_CH_MAX_NUM];

/******************************************************************************
 * �� �� ��:fpgaVerGet
 *
 * ����˵��:FPGA�汾��ȡ
 * ����˵��:��
 * �������:��
 * �������:��
 * �� �� ֵ:��
******************************************************************************/
void fpgaVerGet(void)
{
    Uint8 i = 0;
    for(i = 0; i < 32; i++)
    {
        softWareInfo[i] = FPGA_INFO_REG(i);
    }
}
/******************************************************************************
 * �� �� ��:InitFifo
 *
 * ����˵��:��ʼ������FIFO
 * ����˵��:��
 * �������:DAT_FIFO_TYP *fifo:FIFOָ��
 * �������:��
 * �� �� ֵ:��
******************************************************************************/

static void InitFifo(DAT_FIFO_TYP *fifo)
{
	memset((void *)(fifo->dat), 0, FIFO_MAX_SIZE * sizeof(fifo->dat[0]));
	
	fifo->dep = 0;
	fifo->enp = 0;
}
/******************************************************************************
 * �� �� ��:GetFifoNum
 *
 * ����˵��:��ȡFIFO����Ч����֡����
 * ����˵��:��
 * �������:DAT_FIFO_TYP *fifo:FIFOָ��
 * �������:��
 * �� �� ֵ:��
******************************************************************************/
Uint32 GetFifoNum(DAT_FIFO_TYP *fifo)
{
	Uint32 num = 0;

#if 0
	//û�б���ԭ�Ӳ���������if�ȽϺ�ȷ���˳����֧����ʱ�жϽ�������Ӳ�����
	//�п��ܻ�ı�FIFO��������ķ���
	if( fifo->enp < fifo->dep)
	{
		num = fifo->enp + FIFO_MAX_SIZE - fifo->dep;
	}else
	{
		num = fifo->enp - fifo->dep;
	}
#endif

	num = (fifo->enp - fifo->dep + FIFO_MAX_SIZE) % FIFO_MAX_SIZE;
	if(num < 0)
	{
		num += FIFO_MAX_SIZE;
	}

	if(num > FIFO_MAX_SIZE)
	{
		return 0;
	}


	return num;
}
/******************************************************************************
 * �� �� ��:EnqueueFifo
 *
 * ����˵��:FIFO���
 * ����˵��:��
 * �������:DAT_FIFO_TYP *fifo:FIFOָ��,Uint8 *dat:��Ҫ��ӵ�����,Uint32 size:���ݴ�С
 * �������:��
 * �� �� ֵ:FIFO_OK/FIFO_ERR
******************************************************************************/
static ERR_STA EnqueueFifo(DAT_FIFO_TYP *fifo, Uint8 *dat, Uint32 size)
{
	Uint32 tmp;
	Uint32 i;
	
	for(i = 0; i < size; i++)
	{	
		if(((fifo->enp + 1)%FIFO_MAX_SIZE) == fifo->dep)
		{
				//FIFO��
				return STA_ERR;
		}
		if(size > FIFO_MAX_SIZE)
		{
				 //���ݸ�������������
				return STA_ERR;
		}
		
		fifo->dat[fifo->enp] = dat[i];
		
		tmp = (fifo->enp + 1)%FIFO_MAX_SIZE;
		fifo->enp = tmp;
	}
	
	return STA_OK;
}
/******************************************************************************
 * �� �� ��:DequeueFifo
 *
 * ����˵��:FIFO����
 * ����˵��:��
 * �������:DAT_FIFO_TYP *fifo:FIFOָ��,Uint8 *dat:��Ҫ��ӵ�����
 * �������:��
 * �� �� ֵ:FIFO_OK/FIFO_ERR
******************************************************************************/
static ERR_STA DequeueFifo(DAT_FIFO_TYP *fifo, Uint8 *dat)
{
	Uint32 tmp;
	
	if(fifo->dep == fifo->enp)
	{
			//FIFO��
			return STA_ERR;
	}
	
	*dat = fifo->dat[fifo->dep];
	
	tmp = (fifo->dep + 1)%FIFO_MAX_SIZE;
	fifo->dep = tmp;
	
	return STA_OK;
}

/******************************************************************************
 * �� �� ��:rs422Init
 *
 * ����˵��:rs422��ʼ��
 * ����˵��:��
 * �������:channel:ͨ���ţ�baud:������
 * �������:��
 * �� �� ֵ:STA_OK/STA_ERR
******************************************************************************/
STATUS rs422Init(Uint16 channel,Uint16 baud)
{
    int i = 0;
    if(channel > RS422_CH_MAX_NUM || channel < 1)
    {
        return STA_ERR;
    }
    InitFifo(&RS422_RECV_FIFO[channel-1]);
    return STA_OK;
}

/******************************************************************************
 * �� �� ��:rs422Read
 *
 * ����˵��:rs422���ݶ�ȡ
 * ����˵��:��
 * �������:channel:ͨ���ţ�len:��ȡ����
 * �������:pbuf:�洢��ȡ����
 * �� �� ֵ:��ȡ���ݳ���
******************************************************************************/
ERR_STA rs422Read(Uint16 channel,Uint8 *pbuf,Uint16 len)
{
    Uint32 timeout = 0,sta,CompletionCode;
    Uint32 localaddr = (Uint32)pbuf;
    Uint8 fifoLen = 0;
    do
    {
        timeout++;
        sta = RS422_STA_REG(channel)>> 4;
        if((sta ) != 0)
        {
        	if(sta != 3)
            {
        		fifoLen = RS422_RX_SIZE_REG(channel);
        		if(len > fifoLen)
        		{
        			len = fifoLen;
        			printf("fifolen %d",fifoLen);
        		}
            }
            RS422_FIFO_LENGTH(channel,len);
            if(len & 0x7)
            {
                len += (0x8 - len&0x7);
            }
            timeout = 0;
            do
            {
                timeout++; 
                sta = RS422_STA_REG(channel);
                if((sta & 0x40) != 0)
                {
                    CompletionCode = Keystone_SRIO_DirectIO(localaddr,RS422_TXRX_FIFO(channel),\
                    FPGA_SRIO_BASE_ID,len,1,1,SRIO_PKT_TYPE_NREAD);
                    if(CompletionCode != 0)
                    {
                    	RS422_RX_SIZE_REG_W(channel,0x1);
                        printf("channel %d SRIO read fail CompletionCode %d\r\n",channel,CompletionCode);
                        return STA_ERR;
                    }
                    return STA_OK;
                }
            }while(timeout < 50000);
        }
    }while(timeout < 50000);
    if(timeout == 50000)
    {
        return STA_ERR;
    }

}
void rs422Trans(Uint16 channel,Uint8 *pbuf,Uint16 len)
{
	ERR_STA sta;
	sta = rs422Read(channel,pbuf,len);
	big2little(pbuf,len);
}
/******************************************************************************
 * �� �� ��:rs422Write
 *
 * ����˵��:rs422����д��
 * ����˵��:��
 * �������:channel:ͨ���ţ�len:��ȡ����
 * �������:��
 * �� �� ֵ:STA_OK/STA_ERR
******************************************************************************/
STATUS rs422Write(Uint16 channel,Uint8 *pbuf,Uint16 len)
{
    Uint32 timeout = 0,sta,CompletionCode,fifolen;
    Uint32 localaddr = (Uint32)pbuf;
    //fifolen = RS422_TXFIFO_GET_REG()
    RS422_TX_SIZE_REG(channel,len);
    RS422_CTR_REG(channel,CLR_RX_FIFO | EN_TX);
    if(len & 0x7)
    {
        len += (0x8 - len&0x7);
    }
    do
    {
        timeout++;
        sta = RS422_STA_REG(channel);
        if((sta & 0x3) != 3)
        {
           CompletionCode =  Keystone_SRIO_DirectIO(localaddr,RS422_TXRX_FIFO(channel),\
            FPGA_SRIO_BASE_ID,len,0,0,SRIO_PKT_TYPE_NWRITE);
            RS422_CTR_REG(channel,DIS_TX);
            if(CompletionCode != 0)
            {
                printf("channel %d SRIO write fail CompletionCode %d\r\n",channel,CompletionCode);
                return STA_ERR;
            }
            return STA_OK;
        }
    }while(timeout < 50000);
    return STA_ERR;
}
/******************************************************************************
 * �� �� ��:fpgaSpiInit
 *
 * ����˵��:spi��ʼ��
 * ����˵��:��
 * �������:channel:ͨ���ţ�baud:������
 * �������:��
 * �� �� ֵ:STA_OK/STA_ERR
******************************************************************************/
STATUS fpgaSpiInit(Uint32 channel,Uint32 baud)
{
    int i;
    if(channel > SPI_CH_MAX_NUM || channel < 1)
    {
        return STA_ERR;
    }
    InitFifo(&SPI_RECV_FIFO[channel-1]);
    return STA_OK;
}
/******************************************************************************
 * �� �� ��:fpgaSpiRead
 *
 * ����˵��:spi���ݶ�ȡ
 * ����˵��:��
 * �������:channel:ͨ���ţ�len:��ȡ����
 * �������:pbuf:�洢��ȡ����
 * �� �� ֵ:��ȡ���ݳ���
******************************************************************************/
Uint32 fpgaSpiRead(Uint32 channel,Uint8 *pbuf,Uint32 len)
{
    Uint32 timeout = 0,readCnt = 0;
    Uint8  *rxbuf = pbuf;
    Uint8 fifoLen;
    fifoLen = SPI_RX_SIZE_REG(channel);
    do
    {
        timeout++;
        if(((SPI_STA_REG(channel)>>4)&0x3) != 0)
        {
            rxbuf[readCnt] = (Uint8)SPI_RX_FIFO_REG(channel);
            readCnt++;
            timeout = 0;
        }
        if(readCnt == len)
        {
            break;
        }
    }while(timeout < 50000);
    return readCnt;
}
/******************************************************************************
 * �� �� ��:fpgaSpiWrite
 *
 * ����˵��:spi����д��
 * ����˵��:��
 * �������:channel:ͨ���ţ�len:��ȡ����
 * �������:��
 * �� �� ֵ:STA_OK/STA_ERR
******************************************************************************/
STATUS fpgaSpiWrite(Uint32 channel,Uint8 *pbuf,Uint32 len)
{
    Uint32 timeout = 0,sendCnt = 0;
    Uint8 *txbuf = pbuf;
    SPI_TX_SIZE_REG(channel,len);
    SPI_CTR_REG(channel,CLR_RX_FIFO | EN_TX);
    do
    {
        timeout++;
        if(((SPI_STA_REG(channel))&0x3) != 3)
        {
            SPI_TX_FIFO_REG(channel,txbuf[sendCnt]);
            sendCnt++;
            timeout = 0;
        }
        if(sendCnt == len)
        {
            break;
        }

    }while(timeout < 50000);
    SPI_CTR_REG(channel,DIS_TX);
    if(timeout == 50000)
    {
    	printf("timeout\r\n");
    }
    return STA_ERR;
}


/******************************************************************************
 * �� �� ��:Rs422Recv
 *
 * ����˵��:rs422���ݽ���
 * ����˵��:��
 * �������:channel ͨ����,buf ������ݵ�ָ��,len ����
 * �������:��
 * �� �� ֵ:�ɹ���ȡ���ݵĳ���
******************************************************************************/
uint16_t Rs422Recv(uint8_t channel, uint8_t *buf, uint16_t len)
{
    int32_t fifo_len;
    uint16_t i;
    uint8_t dat = 0;

    fifo_len = GetFifoNum(&RS422_RECV_FIFO[channel]);

    fifo_len = (uint16_t)fifo_len;

    if(fifo_len < len)
    {
        len = fifo_len;
    }
    for(i=0;i<len;i++)
    {
        if(DequeueFifo(&RS422_RECV_FIFO[channel], &dat) == STA_ERR)
        {
            return i;
        }
        buf[i] = dat;
    }
    return len;
}
/******************************************************************************
 * �� �� ��:SpiRecv
 *
 * ����˵��:spi���ݽ���
 * ����˵��:��
 * �������:channel ͨ����,buf ������ݵ�ָ��,len ����
 * �������:��
 * �� �� ֵ:�ɹ���ȡ���ݵĳ���
******************************************************************************/
uint16_t SpiRecv(uint8_t channel, uint8_t *buf, uint16_t len)
{
    int32_t fifo_len;
    uint16_t i;
    uint8_t dat = 0;

    fifo_len = GetFifoNum(&SPI_RECV_FIFO[channel]);

    fifo_len = (uint16_t)fifo_len;

    if(fifo_len < len)
    {
        len = fifo_len;
    }
    for(i=0;i<len;i++)
    {
        if(DequeueFifo(&SPI_RECV_FIFO[channel], &dat) == STA_ERR)
        {
            return i;
        }
        buf[i] = dat;
    }
    return len;
}


/******************************************************************************
 * �� �� ��:Spi_Rs422Isr
 *
 * ����˵��:spi/rs422�жϷ�����
 * ����˵��:��
 * �������:��
 * �������:��
 * �� �� ֵ:��
******************************************************************************/
ERR_STA Spi_Rs422Isr(void)
{
    Uint32 fpgaIntSta,i,sta;
    Uint8 dat;
    fpgaIntSta = M_INT_STA_REG;
    
    if((fpgaIntSta & SPI_INT) == 0x2)
    {
        for(i = 0; i < 6; i++)
        {
            sta = SPI_STA_REG(i);
            if(((sta >> 15) == 1) && ((sta  >> 4) != 0))
            {
                SPI_CTR_REG(i,CLR_RX_INT | EN_RX_INT);
               dat =  (Uint8)SPI_RX_FIFO_REG(i);
               if(EnqueueFifo(&SPI_RECV_FIFO[i],&dat,1) == STA_ERR)
               {
                    return STA_ERR;
               }
            }
        }

    }
    
    if((fpgaIntSta & RS422_INT) == 0x1)
    {
        for(i = 0; i < 12; i++)
        {
            sta = RS422_STA_REG(i);
            if(((sta >> 15) == 1) && ((sta  >> 4) != 0))
            {
                RS422_CTR_REG(i,CLR_RX_INT | EN_RX_INT);
               dat =  (Uint8)RS422_RX_FIFO_REG(i);
               if(EnqueueFifo(&RS422_RECV_FIFO[i],&dat,1) == STA_ERR)
               {
                    return STA_ERR;
               }
            }
        }

    }
}


Int32 Keystone_SRIO_DirectIO(Uint32 uiLocalAddress, Uint32 uiRemoteAddress,
    Uint32 uiDestID, Uint32 uiByteCount, Uint32 uiPort, Uint32 uiLSU_No,
    SRIO_Packet_Type packetType)
{
    SRIO_LSU_Transfer lsuTransfer;


    lsuTransfer.rioAddressMSB=0;
    lsuTransfer.rioAddressLSB_ConfigOffset= uiRemoteAddress;
    lsuTransfer.localDspAddress= uiLocalAddress;
    lsuTransfer.bytecount= uiByteCount;
    lsuTransfer.packetType= packetType;
    lsuTransfer.dstID= uiDestID;
    lsuTransfer.doorbellInfo= 0;
    lsuTransfer.waitLsuReady= 1;
    lsuTransfer.lsuNum= uiLSU_No;
    lsuTransfer.doorbellValid = 0;
    lsuTransfer.intrRequest = 0;
    lsuTransfer.supGoodInt = 0;
    lsuTransfer.priority = 0;
    lsuTransfer.outPortID = uiPort;
    lsuTransfer.idSize = 0;
    lsuTransfer.srcIDMap = 0;
    lsuTransfer.hopCount = 0;

    KeyStone_SRIO_LSU_transfer(&lsuTransfer);

    return KeyStone_SRIO_wait_LSU_completion(uiLSU_No,
        lsuTransfer.transactionID, lsuTransfer.contextBit);

}


#define BIGLITTLE(BIG) (((BIG&0xff) << 24)|((BIG&0xff00) << 8)|((BIG >>24)& 0xff)|(( BIG&0xff0000)>>8))

void big2little(UINT8* pbuf, int len)
{
	UINT8 remain_num,i;
    UINT32 temph ,templ;
    UINT64 u64_temp;
	UINT8 *remain_buf;
    UINT64 *buf = (UINT64 *)pbuf;
    while(len > 0)
    {
    	templ = *buf & 0xffffffff;
    	temph = (*buf >> 32) & 0xffffffff;
    	u64_temp = BIGLITTLE(templ);
    	u64_temp = (u64_temp <<32) | BIGLITTLE(temph);
    	*buf = u64_temp;
    	if(len < 8)
    	{
    		remain_num = 8 - len;
    		remain_buf = (UINT8 *)buf;
    		for(i = 0; i < len; i++)
    		{
    			remain_buf[i] = remain_buf[i+remain_num];
    		}
    		memset(remain_buf+len,0x0,remain_num);
    	}
    	buf++;
    	len -= 8;
    }
}


