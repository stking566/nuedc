
#include "./BSP/ADC/adc.h"
#include "./SYSTEM/delay/delay.h"


ADC_HandleTypeDef g_adc_handle;   /* ADC句柄 */

/**
 * @brief       ADC初始化函数
 *   @note      本函数支持ADC1/ADC2任意通道, 但是不支持ADC3
 *              我们使用12位精度, ADC采样时钟=12M, 转换时间为: 采样周期 + 12.5个ADC周期
 *              设置最大采样周期: 239.5, 则转换时间 = 252 个ADC周期 = 21us
 * @param       无
 * @retval      无
 */
 
 const  PhotoRes_TypeDef GL5528[281]=
{
{40000,	1},{26350,	2},{20640,	3},{17360,	4},{15170,	5},
{13590,	6},{12390,	7},{11430,	8},{10650,	9},{9990,	10},
{9440,	11},{8950,	12},{8530,	13},{8160,	14},{7830,	15},
{7530,	16},{7260,	17},{7010,	18},{6790,	19},{6580,	20},
{6390,	21},{6210,	22},{6050,	23},{5900,	24},{5750,	25},
{5620,	26},{5490,	27},{5370,	28},{5260,	29},{5160,	30},
{5050,	31},{4960,	32},{4870,	33},{4780,	34},{4700,	35},
{4620,	36},{4540,	37},{4470,	38},{4400,	39},{4330,	40},
{4270,	41},{4210,	42},{4150,	43},{4090,	44},{4040,	45},
{3980,	46},{3930,	47},{3880,	48},{3840,	49},{3790,	50},
{3740,	51},{3700,	52},{3660,	53},{3620,	54},{3580,	55},
{3540,	56},{3500,	57},{3460,	58},{3430,	59},{3390,	60},
{3360,	61},{3330,	62},{3300,	63},{3270,	64},{3230,	65},
{3210,	66},{3180,	67},{3150,	68},{3120,	69},{3090,	70},
{3070,	71},{3040,	72},{3020,	73},{2990,	74},{2970,	75},
{2940,	76},{2920,	77},{2900,	78},{2880,	79},{2850,	80},
{2830,	81},{2810,	82},{2790,	83},{2770,	84},{2750,	85},
{2730,	86},{2710,	87},{2690,	88},{2680,	89},{2660,	90},
{2640,	91},{2620,	92},{2610,	93},{2590,	94},{2570,	95},
{2560,	96},{2540,	97},{2530,	98},{2510,	99},{2490,	100},
{2480,	101},{2460,	102},{2450,	103},{2440,	104},{2420,	105},
{2410,	106},{2390,	107},{2380,	108},{2370,	109},{2360,	110},
{2340,	111},{2330,	112},{2320,	113},{2300,	114},{2290,	115},
{2280,	116},{2270,	117},{2260,	118},{2250,	119},{2230,	120},
{2220,	121},{2210,	122},{2200,	123},{2190,	124},{2180,	125},
{2170,	126},{2160,	127},{2150,	128},{2140,	129},{2130,	130},
{2120,	131},{2110,	132},{2100,	133},{2090,	134},{2080,	135},
{2070,	136},{2060,	137},{2050,	138},{2040,	139},{2030,	141},
{2020,	142},{2010,	143},{2000,	144},{1990,	145},{1980,	147},
{1970,	148},{1960,	149},{1950,	150},{1940,	152},{1930,	153},
{1920,	154},{1910,	155},{1900,	157},{1890,	158},{1880,	160},
{1870,	161},{1860,	162},{1850,	164},{1840,	165},{1830,	167},
{1820,	168},{1810,	170},{1800,	171},{1790,	173},{1780,	175},
{1770,	176},{1760,	178},{1750,	180},{1740,	181},{1730,	183},
{1720,	185},{1710,	187},{1700,	188},{1690,	190},{1680,	192},
{1670,	194},{1660,	196},{1650,	198},{1640,	200},{1630,	202},
{1620,	204},{1610,	206},{1600,	208},{1590,	210},{1580,	212},
{1570,	215},{1560,	217},{1550,	219},{1540,	222},{1530,	224},
{1520,	226},{1510,	229},{1500,	231},{1490,	234},{1480,	237},
{1470,	239},{1460,	242},{1450,	245},{1440,	248},{1430,	250},
{1420,	253},{1410,	256},{1400,	259},{1390,	262},{1380,	266},
{1370,	269},{1360,	272},{1350,	275},{1340,	279},{1330,	282},
{1320,	286},{1310,	289},{1300,	293},{1290,	297},{1280,	300},
{1270,	304},{1260,	308},{1250,	312},{1240,	317},{1230,	321},
{1220,	325},{1210,	330},{1200,	334},{1190,	339},{1180,	344},
{1170,	348},{1160,	353},{1150,	358},{1140,	364},{1130,	369},
{1120,	374},{1110,	380},{1100,	386},{1090,	391},{1080,	397},
{1070,	403},{1060,	410},{1050,	416},{1040,	423},{1030,	430},
{1020,	436},{1010,	444},{1000,	451},{990,	458},{980,	466},
{970,	474},{960,	482},{950,	491},{940,	499},{930,	508},
{920,	517},{910,	526},{900,	536},{890,	546},{880,	556},
{870,	567},{860,	578},{850,	589},{840,	600},{830,	612},
{820,	625},{810,	637},{800,	650},{790,	664},{780,	678},
{770,	692},{760,	707},{750,	723},{740,	739},{730,	756},
{720,	773},{710,	791},{700,	809},{690,	829},{680,	849},
{670,	869},{660,	891},{650,	914},{640,	937},{630,	961},
{620,	987},
};
 
 
void adc_init(void)
{
    g_adc_handle.Instance = ADC_ADCX;                        /* 选择哪个ADC */
    g_adc_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;       /* 数据对齐方式：右对齐 */
    g_adc_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;       /* 非扫描模式，仅用到一个通道 */
    g_adc_handle.Init.ContinuousConvMode = DISABLE;          /* 关闭连续转换模式 */
    g_adc_handle.Init.NbrOfConversion = 1;                   /* 赋值范围是1~16，本实验用到1个规则通道序列 */
    g_adc_handle.Init.DiscontinuousConvMode = DISABLE;       /* 禁止规则通道组间断模式 */
    g_adc_handle.Init.NbrOfDiscConversion = 0;               /* 配置间断模式的规则通道个数，禁止规则通道组间断模式后，此参数忽略 */
    g_adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START; /* 触发转换方式：软件触发 */
    HAL_ADC_Init(&g_adc_handle);                             /* 初始化 */

    HAL_ADCEx_Calibration_Start(&g_adc_handle);              /* 校准ADC */
}

/**
 * @brief       ADC底层驱动，引脚配置，时钟使能
                此函数会被HAL_ADC_Init()调用
 * @param       hadc:ADC句柄
 * @retval      无
 */
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
    if(hadc->Instance == ADC_ADCX)
    {
        GPIO_InitTypeDef gpio_init_struct;
        RCC_PeriphCLKInitTypeDef adc_clk_init = {0};
        
        ADC_ADCX_CHY_CLK_ENABLE();                                /* 使能ADCx时钟 */
        ADC_ADCX_CHY_GPIO_CLK_ENABLE();                           /* 开启GPIO时钟 */

        /* 设置ADC时钟 */
        adc_clk_init.PeriphClockSelection = RCC_PERIPHCLK_ADC;    /* ADC外设时钟 */
        adc_clk_init.AdcClockSelection = RCC_ADCPCLK2_DIV6;       /* 分频因子6时钟为72M/6=12MHz */
        HAL_RCCEx_PeriphCLKConfig(&adc_clk_init);                 /* 设置ADC时钟 */

        /* 设置AD采集通道对应IO引脚工作模式 */
        gpio_init_struct.Pin = ADC_ADCX_CHY_GPIO_PIN;             /* ADC通道IO引脚 */
        gpio_init_struct.Mode = GPIO_MODE_ANALOG;                 /* 模拟 */
        HAL_GPIO_Init(ADC_ADCX_CHY_GPIO_PORT, &gpio_init_struct);
    }
}

/**
 * @brief       设置ADC通道采样时间
 * @param       adcx : adc句柄指针,ADC_HandleTypeDef
 * @param       ch   : 通道号, ADC_CHANNEL_0~ADC_CHANNEL_17
 * @param       stime: 采样时间  0~7, 对应关系为:
 *   @arg       ADC_SAMPLETIME_1CYCLE_5, 1.5个ADC时钟周期        ADC_SAMPLETIME_7CYCLES_5, 7.5个ADC时钟周期
 *   @arg       ADC_SAMPLETIME_13CYCLES_5, 13.5个ADC时钟周期     ADC_SAMPLETIME_28CYCLES_5, 28.5个ADC时钟周期
 *   @arg       ADC_SAMPLETIME_41CYCLES_5, 41.5个ADC时钟周期     ADC_SAMPLETIME_55CYCLES_5, 55.5个ADC时钟周期
 *   @arg       ADC_SAMPLETIME_71CYCLES_5, 71.5个ADC时钟周期     ADC_SAMPLETIME_239CYCLES_5, 239.5个ADC时钟周期
 * @param       rank: 多通道采集时需要设置的采集编号,
                假设你定义channle1的rank=1，channle2 的rank=2，
                那么对应你在DMA缓存空间的变量数组AdcDMA[0] 就i是channle1的转换结果，AdcDMA[1]就是通道2的转换结果。 
                单通道DMA设置为 ADC_REGULAR_RANK_1
 *   @arg       编号1~16：ADC_REGULAR_RANK_1~ADC_REGULAR_RANK_16
 * @retval      无
 */
void adc_channel_set(ADC_HandleTypeDef *adc_handle, uint32_t ch, uint32_t rank, uint32_t stime)
{
    ADC_ChannelConfTypeDef adc_ch_conf;
    
    adc_ch_conf.Channel = ch;                            /* 通道 */
    adc_ch_conf.Rank = rank;                             /* 序列 */
    adc_ch_conf.SamplingTime = stime;                    /* 采样时间 */
    HAL_ADC_ConfigChannel(adc_handle, &adc_ch_conf);     /* 通道配置 */
}

/**
 * @brief       获得ADC转换后的结果
 * @param       ch: 通道值 0~17，取值范围为：ADC_CHANNEL_0~ADC_CHANNEL_17
 * @retval      无
 */
uint32_t adc_get_result(uint32_t ch)
{
    adc_channel_set(&g_adc_handle , ch, ADC_REGULAR_RANK_1, ADC_SAMPLETIME_239CYCLES_5);    /* 设置通道，序列和采样时间 */

    HAL_ADC_Start(&g_adc_handle);                            /* 开启ADC */
    HAL_ADC_PollForConversion(&g_adc_handle, 10);            /* 轮询转换 */
    return (uint16_t)HAL_ADC_GetValue(&g_adc_handle);        /* 返回最近一次ADC1规则组的转换结果 */
}

/**
 * @brief       获取通道ch的转换值，取times次,然后平均
 * @param       ch      : 通道号, 0~17
 * @param       times   : 获取次数
 * @retval      通道ch的times次转换结果平均值
 */
uint32_t adc_get_result_average(uint32_t ch, uint8_t times)
{
    uint32_t temp_val = 0;
    uint8_t t;

    for (t = 0; t < times; t++)     /* 获取times次数据 */
    {
        temp_val += adc_get_result(ch);
        delay_ms(5);
    }

    return temp_val / times;        /* 返回平均值 */
}
unsigned short GetLux(uint32_t PhotoResistor)
{
  unsigned short lux = 0;
  //查表法，根据电阻值得出光照度
  for(int i = 0 ; i < 281 ; i++)
  {
    if (PhotoResistor > GL5528[i].ohm)
    {
      lux = GL5528[i].lux;
      break;
    }
  }
  return lux;
}







