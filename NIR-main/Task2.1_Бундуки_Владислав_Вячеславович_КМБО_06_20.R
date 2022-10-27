library("lmtest")
library("GGally")
library("car")

data = swiss
help(swiss)

#Вариант 2 Бундуки Владислав КМБО-06-20

#Объясняемая переменная Agriculture , регрессоры: Fertility, Education, Catholic
model = lm(Agriculture ~ Fertility + Education  + Catholic, data)

# 1) проверка на линейную зависимость среди регрессоров
model_t = lm(Fertility ~ Catholic  + Education, data)
vif(model_t)
#Education  Catholic 
#1.024247  1.024247 
#из полученных данных, а именно, что vif по всем параметрам < 5, мы видим, что объясняющие переменные линейно независимы

#проверим R^2
model_1 = lm(Agriculture ~ Fertility + Education, data)
summary(model_1)
#Arg = 85.7253 + (-0.2)*Fer + (-1.7)*Edu
#R^2 = 0.41 , p-характеристика =  6.707e-06
#R^2 низкий => нет строгой линейной зависимости

model_2 = lm(Agriculture ~ Fertility + Catholic, data)
summary(model_2)
#Arg = 16.7384 + (0.38)*Fer + (0.16)*Cat
#R^2 = 0.2 , p-характеристика =  0.008134
#R^2 очень низкий => переменные почти не связаны между собой
#p-характеристика высокая (возможны существенные отличия реальных данных, от данных модели)

model_3 = lm(Agriculture ~ Education  + Catholic, data)
summary(model_3)
#Arg = 59.06 + (-1.4)*Edu + (0.17)*Cat
#R^2 = 0.5 , p-характеристика = 2.104e-07
#R^2 низкий => нет строгой линейной зависимости

# 2)Строим линейную модель по 3-ем регрессорам
model
summary(model)
#Agriculture = 117.2729 + (-0.78)*Fertility + (-2.01)*Edu + (0.26)Cat
#R^2 =  0.582 , p = 2.956e-08
#R^2 не высокий => нельзя сделать корректные выводы
# p значение низкое => реальные данные мало будут отличаться от данных модели

# р-характеристика у Fertility = (**)
# р-характеристика у Education = (***)
# р-характеристика у Catholic = (***)

# 3)Введем в модель логарифмы регрессоров и сравним их для поиска лучшей  
modele_log_1 = lm(Agriculture ~ log(Fertility) + log(Education)  + log(Catholic), data)
summary(modele_log_1)
vif(modele_log_1)
#R^2 = 0.50 - модель ухудшилась
#Agriculture = 120.271 + (-8.717)*Fertility + (-20.352)*Edu + ( 3.426 )Cat

#log(Fertility) log(Education)  log(Catholic) 
#1.605793       1.490099       1.103041 

modele_log_2 = lm(Agriculture ~ log(Fertility) + log(Education)  + Catholic, data)
summary(modele_log_2)
vif(modele_log_2)
#R^2 = 0.5394 - модель ухудшилась
#Agriculture = 145.97625 + (-14.4779)*Fertility + (-19.54853)*Edu + (0.17028 )Cat

#log(Fertility) log(Education) Catholic 
#1.656365       1.458331       1.184675 


modele_log_3 = lm(Agriculture ~ log(Fertility) + Education  + log(Catholic), data)
summary(modele_log_3)
vif(modele_log_3)
#R^2 = 0.5246 - модель ухудшилась
#Agriculture =  255.9569 + (-46.5763)*Fertility + (-2.2245  )*Edu + (5.5737 )Cat

#log(Fertility) Education  log(Catholic) 
#2.616193       2.426323       1.216809 


modele_log_4 = lm(Agriculture ~ Fertility + log(Education)  + log(Catholic), data)
summary(modele_log_4)
vif(modele_log_4)
#R^2 = 0.5018 - модель ухудшилась
#Agriculture = 97.0689 + (-0.1948)*Fertility + (-20.7370)*Edu + (3.6925)Cat

# Fertility log(Education)  log(Catholic) 
#1.626027       1.429427       1.180360 


modele_log_5 = lm(Agriculture ~ log(Fertility) + Education  + Catholic, data)
summary(modele_log_5)
vif(modele_log_5)
#R^2 = 0.5821 - модель улудшилась
#Agriculture = 286.99567 + (-52.62785)*Fertility + (-2.13538)*Edu + ( 0.24021)Cat

#log(Fertility)  Education     Catholic 
#2.606621       2.255065       1.241080 


modele_log_6 = lm(Agriculture ~ Fertility + Education  + log(Catholic), data)
summary(modele_log_6)
vif(modele_log_6)
#R^2 = 0.5199 - модель ухудшилась
#Agriculture = 103.3117 + (-0.6653)*Fertility + ( -2.1044)*Edu + (5.8601)Cat

#Fertility     Education log(Catholic) 
#2.345216      2.060489      1.312589 


modele_log_7 = lm(Agriculture ~ Fertility + log(Education)  + Catholic, data)
summary(modele_log_7)
vif(modele_log_7)
#R^2 =0.5469 - модель ухудшилась
#Agriculture = 106.48306 + (-0.30771)*Fertility + (-19.93094)*Edu + (0.18471)Cat

# Fertility log(Education)       Catholic 
#1.690517       1.383282       1.277755

#Из всех моделей только у modele_log_5 улучшился результат на 0.001

# 4) Введем в модель всевозможные произведения пар регрессоров, в том числе и квадраты регрессоров
model_fin_1 = lm(Agriculture ~ Fertility + Education  + Catholic + I(Fertility^2) + I(Education^2) + I(Catholic^2) + I(Fertility*Education) + I(Fertility*Catholic) + I(Education*Catholic) + I(Fertility*Education*Catholic), data)
summary(model_fin_1) #R^2 = 0.649
vif(model_fin_1)
#Fertility                           Education                            Catholic                      I(Fertility^2)                      I(Education^2) 
#1202.45759                           715.22375                           698.63130                          1073.14964                            65.46627 
#I(Catholic^2)            I(Fertility * Education)             I(Fertility * Catholic)             I(Education * Catholic) I(Fertility * Education * Catholic) 
#102.91025                           248.25376                           854.36665                           417.27846                           262.25286 
model_fin_2 = lm(Agriculture ~ Education  + Catholic + I(Fertility^2) + I(Education^2) + I(Catholic^2) + I(Fertility*Education) + I(Fertility*Catholic) + I(Education*Catholic) + I(Fertility*Education*Catholic), data)
summary(model_fin_2)#R^2 = 0.6438
vif(model_fin_2)
#Education                            Catholic                      I(Fertility^2)                      I(Education^2)                       I(Catholic^2) 
#526.60606                           493.37868                            27.02345                            37.92860                            97.00687 
#I(Fertility * Education)             I(Fertility * Catholic)             I(Education * Catholic) I(Fertility * Education * Catholic) 
#194.98215                           528.73345                           335.38100                           223.88949 
model_fin_3 = lm(Agriculture ~ Education  + Catholic + I(Fertility^2) + I(Education^2) + I(Catholic^2) + I(Fertility*Education) + I(Education*Catholic) + I(Fertility*Education*Catholic), data)
summary(model_fin_3)#R^2 = 0.6347
vif(model_fin_3)
#Education                            Catholic                      I(Fertility^2)                      I(Education^2)                       I(Catholic^2) 
#221.168732                          107.227897                            5.691261                           33.929044                           96.719808 
#I(Fertility * Education)             I(Education * Catholic) I(Fertility * Education * Catholic) 
#73.100041                           84.758256                           61.428962 
model_fin_4 = lm(Agriculture ~ Catholic + I(Fertility^2) + I(Education^2) + I(Catholic^2) + I(Fertility*Education) + I(Education*Catholic) + I(Fertility*Education*Catholic), data)
summary(model_fin_4)#R^2 = 0.6239
vif(model_fin_4)
#Catholic                      I(Fertility^2)                      I(Education^2)                       I(Catholic^2)            I(Fertility * Education) 
#105.927952                            3.495721                           11.408063                           96.005149                            5.186397 
#I(Education * Catholic) I(Fertility * Education * Catholic) 
#56.316235                           43.419420 
model_fin_5 = lm(Agriculture ~ I(Fertility^2) + I(Education^2) + I(Catholic^2) + I(Fertility*Education) + I(Education*Catholic) + I(Fertility*Education*Catholic), data)
summary(model_fin_5)#R^2 = 0.6
vif(model_fin_5)
#I(Fertility^2)                      I(Education^2)                       I(Catholic^2)            I(Fertility * Education)             I(Education * Catholic) 
#3.260152                           10.832919                            4.490278                            5.037852                           46.054565 
#I(Fertility * Education * Catholic) 
#40.642469 
model_fin_6 = lm(Agriculture ~ I(Fertility^2) + I(Education^2) + I(Catholic^2) + I(Fertility*Education) + I(Fertility*Education*Catholic), data)
#Agriculture =  7.919e+01 + (-3.195e-03)*Fertility^2 + (-8.119e-03)*Edu^2 + (2.724e-03)Cat^2 + (-2.640e-02)*(Fertility*Education) + (-6.148e-05)*(Fertility*Education*Catholic)
summary(model_fin_6)#R^2 = 0.5971
vif(model_fin_6)
#I(Fertility^2)                      I(Education^2)                       I(Catholic^2)            I(Fertility * Education) I(Fertility * Education * Catholic) 
#2.158891                            3.169903                            4.399625                            3.395697                            4.326309 


#Вывод: Agriculture =  7.919e+01 + (-3.195e-03)*Fertility^2 + (-8.119e-03)*Edu^2 + (2.724e-03)Cat^2 + (-2.640e-02)*(Fertility*Education) + (-6.148e-05)*(Fertility*Education*Catholic)
#это лучшая модель ,т.к. VIF < 6