# Missing_data_process
This is a project for missing data process with time and space relationship.
## 1. Intorduction 简介
This code is just for static data, not for streaming data.<br>
程序主要用来做缺失数据处理.

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


## 3. 实现
实现框图如下所示<br>
![image](https://github.com/qinchao0525/Missing_data_process/blob/master/picture/processing_struct.jpg)
<center> 处理框架 </center>

# 流式数据处理
## 1. 滑动窗口模型
![image](https://github.com/qinchao0525/Missing_data_process/blob/master/picture/flow_window.png)<br>

## 2. 处理流程图
![image](https://github.com/qinchao0525/Missing_data_process/blob/master/picture/struct_of_streamdata.png)

## 3. 添加的新实现
完成了新的代码编程，完成了流失处理代码编程，暂时缺乏业务逻辑测试。<br>
