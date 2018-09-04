# Missing_data_process
This is a project for missing data process with time and space relationship.
## 1. Intorduction 简介
This code is just for static data, not for streaming data.<br>
程序主要用来做缺失数据处理（静态和流失数据处理）.

## 2. Algorithms 算法
### 2.1	基于插值法的缺失数据填充方法
在网络中，节点的数据相关性的强弱由相关系数的大小所决定。在该方法中采用皮尔逊相关系数求各项数据的相关性<br>
相关系数是按照积差方法计算，同样以两变量与各自平均值的离差为基础，通过两个离差相乘来反映两变量之间的相关程度。 <br>
规定相关系数大于0.8时为强相关数据。按照如下方法去估算缺失数据值：<br>
1）	计算缺失数据项与已知完备的数据项的相关性系数，并把相关性大于0.8的数据项按照相关性从高到低排序；<br>
2）	利用线性插值法对数据进行估计<br>
3）	判断数据序列是否是稳态序列，如果是非稳态序列，进行查分处理，直到变成稳态序列。<br>
4）	定阶，找到是AIC（Akaike信息准则，它考虑了模型的统计拟合度以及用来拟合的参数数目。AIC值越小，模型越优，它说明模型用较少的参数获得了足够的拟合度）最小的模型。<br>
5）	预测，根据已有的数据对缺失数据进行估计。<br>

### 2.2 基于灰度预测的缺失数据填充方法
灰色系统理论是解决具有不确定性关系对象间问题的一类研究方法，其核心内容灰预测模型模型，在预测与控制、模式识别以及其他很多工程领域得到广泛的应用。<br>
利用灰色系统理论对缺失的观测数据进行处理，即是利用一个灰数去替代缺失的数据。根据灰色系统理论，灰数是指有确定的外延而无确定内涵的数。<br>
在动态定位中，缺失的观测数据值一般应该位于与其相临的两个或若干个观测数据之间。这两个或若干个观测数据就可以看作是这个缺失数据的外推。<br>

### 2.3 空间相关性数据填充方法（SKNN）
空间相关性数据填充主要是基于传感器空间位置的相关性，再空间上具有相关性的传感器，对于某一属性的检测可能是存在相关联的，利用这种关联特性，可以<br>
对数据进行k近邻数据填充。
## 3. 实现
实现框图如下所示<br>
![image](https://github.com/qinchao0525/Missing_data_process/blob/master/picture/processing_struct.jpg)
<center> 处理框架 </center>
该图为静态数据缺失处理总框架图，具体流程如下：<br>

# 流式数据处理
## 1. 滑动窗口模型
![image](https://github.com/qinchao0525/Missing_data_process/blob/master/picture/flow_window.png)<br>
滑动窗口模型在于对流式数据处理，处理的想法初衷在于用部分缓冲区去存下，存下的数据进行处理，然后边存边处理，因此数据处理的速率取决于缓冲区的大小，而且还有处理算法的优劣。改变滑动窗口的大小，影响处理数据的快慢，同时影响处理速度。
## 2. 处理流程图
![image](https://github.com/qinchao0525/Missing_data_process/blob/master/picture/struct_of_streamdata.png)<br>
说明：<br>
对于缺失数据流，首先对确实数据进行缺失判断，对具有缺失的数据进行处理。处理的过程首先需要确定滑动窗口的大小，然后固定滑动窗口，<br>
在滑动窗口的内部采用静态不完备信息处理，然后得到完备数据。由于数据流是源源不断进入缺失处理系统，因此，在处理完部分后，再对缓存<br>
中的数据进行处理，得到完备数据流。
## 3.测试数据的产生
进入目录：https://github.com/qinchao0525/Missing_data_process/tree/streampro/Stream_data_process/Streamdata<br>
在目录下make，可以生成数据发生器，然后使用./执行。
使用方法：<br>
Explain:<br>
usage -kb +datarate.<br>
k---for kb.<br>
b---for b.<br>
## 4.流式数据处理
