install.packages("devtools")
devtools::install_github("bdemeshev/rlms")

library("lmtest")
library("rlms")
library("dplyr")
library("GGally")
library("car")
library("sandwich")


data <- rlms_read("C:\\Users\\vladb\\Downloads\\r22i_os26c.sav")
glimpse(data)
data2 = select(data, rj13.2, r_age, rh5, r_educ, status, rj6.2, r_marst)

#Убираем строки с NA
data2 = na.omit(data2)
glimpse(data2)

#зарплата c элементами нормализации
data2$rj13.2
sal = as.numeric(data2$rj13.2)
sal1 = as.character(data2$rj13.2)
sal2 = lapply(sal1, as.integer)
sal = as.numeric(unlist(sal2))
mean(sal)
data2["salary"] = (sal - mean(sal)) / sqrt(var(sal))
data2["salary"]

#возраст c элементами нормализации
age1 = as.character(data2$r_age)
age2 = lapply(age1, as.integer)
age3 = as.numeric(unlist(age2))
data2["age"]= (age3 - mean(age3)) / sqrt(var(age3))
data2["age"]

#пол
#data2["sex"]=data2$rh5
#data2["sex"] = lapply(data2$rh5, as.character)
data2$sex = as.numeric(data2$rh5)
data2$sex[which(data2$sex!='1')] <- 0 #женский
data2$sex[which(data2$sex=='1')] <- 1 #мужской


#образование
#data2["r_educ"] = data2$r_educ
#data2["r_educ"] = lapply(data2$r_educ, as.character)
#data2["higher_educ"] = data2$r_educ
data2$r_educ = as.numeric(data2$r_educ)
data2$r_educ[which(data2$r_educ=='21')] <- 1 #есть диплом о высшем образовании
data2$r_educ[which(data2$r_educ=='22')] <- 1 #аспирантура и т.п. без диплома
data2$r_educ[which(data2$r_educ=='23')] <- 1 #аспирантура и т.п. с дипломом

#населенный пункт
#data2["status1"]=data2$status
#data2["status1"] = lapply(data2$status, as.character)
data2$status1 = as.numeric(data2$status)
data2$status1[which(data2$status1=='1')] <- 1 #областной центр
data2$status1[which(data2$status1=='2')] <- 1 #город


#продолжительность рабочей недели
dur1 = as.character(data2$rj6.2)
dur2 = lapply(dur1, as.integer)
dur3 = as.numeric(unlist(dur2))
data2["dur"] = (dur3 - mean(dur3)) / sqrt(var(dur3))

#семейное положение
#data2["wed"]= data2$r_marst
#data2["wed"] = lapply(data2$r_marst, as.character)
data2$wed = as.numeric(data2$r_marst)
data2$wed[which(data2$wed=='1')] <- 1 #никогда не были в браке
data2$wed[which(data2$wed=='2')] <- 1 # Состоят в зарегистрированном браке


#data2["wed2"] = lapply(data2["wed"], as.character)
data2$wed2 = as.numeric(data2$r_marst)
data2$wed2[which(data2$wed=='4')] <- 1 # Разведены
data2$wed2[which(data2$wed=='5')] <- 1 # Bдовец/вдова

#data2$wed2 = as.numeric(data2$wed2)

#data2["wed3"] = lapply(data2["wed"], as.character)
data2$wed3 = as.numeric(data2$r_marst)
data2$wed3[which(data2$wed=='3')] <- 1 # Живете вместе, но не зарегистрированы
data2$wed3[which(data2$wed=='6')] <- 1 # ОФИЦИАЛЬНО ЗАРЕГИСТРИРОВАНЫ, НО ВМЕСТЕ НЕ ПРОЖИВАЮТ

data3 = select(data2, salary, age, sex, r_educ, status1, dur, wed, wed2, wed3)

#построение зависимостей для данных 
model = lm(data = data3, salary~age + sex + r_educ + status1 + dur + wed + wed2 + wed3)
summary(model)
vif(model)
#R^2 = 0.1339 - очень низкий
#p-характеристика у всех значений (***), кроме wed2 (**)

# 2. Поэкспериментируйте с функциями вещественных параметров: используйте логарифм и степени (хотя бы от 0.1 до 2 с шагом 0.1).
model_test_1 = lm(data = data3, salary~ age + sex + r_educ + status1 + dur + wed + wed2 + wed3 + I(dur^0.1) + I(age^0.1))
summary(model_test_1)
vif(model_test_1)
#R^2 = 0.1691
#р - ухудшился
#vif <= 7

model_test_1 = lm(data = data3, salary~ age + sex + r_educ + status1 + dur + wed + wed2 + wed3 + I(dur^0.2) + I(age^0.2))
summary(model_test_1)
vif(model_test_1)
#R^2 = 0.1695
#р - ухудшился
#vif <= 7

model_test_1 = lm(data = data3, salary~ age + sex + r_educ + status1 + dur + wed + wed2 + wed3 + I(dur^0.3) + I(age^0.3))
summary(model_test_1)
vif(model_test_1)
#R^2 = 0.17
#р - ухудшился
#vif <= 10 ~ есть линейнай зависимость

model_test_1 = lm(data = data3, salary~ age + sex + r_educ + status1 + dur + wed + wed2 + wed3 + I(age^0.4) + I(dur^0.4))
summary(model_test_1)
vif(model_test_1)
#R^2 = 0.1704
#р - ухудшился
#vif <= 13 ~ есть линейнай зависимость

model_test_1 = lm(data = data3, salary~ age + sex + r_educ + status1 + dur + wed + wed2 + wed3 + I(dur^0.4))
summary(model_test_1)
vif(model_test_1)
#R^2 = 0.1413
#р - ухудшился
#vif <= 14 ~ есть линейнай зависимость

model_test_1 = lm(data = data3, salary~ age + sex + r_educ + status1 + dur + wed + wed2 + wed3 + I(age^0.4))
summary(model_test_1)
vif(model_test_1)
#R^2 = 0.1595
#р - ухудшился
#vif <= 11 ~ есть линейнай зависимость

model_test_1 = lm(data = data3, salary~ age + sex + r_educ + status1 + dur + wed + wed2 + wed3 + I(dur^0.4))
summary(model_test_1)
vif(model_test_1)
#R^2 = 0.1413
#р - ухудшился
#vif <= 14 ~ есть линейнай зависимость

model_test_1 = lm(data = data3, salary~ age + sex + r_educ + status1 + dur + wed + wed2 + wed3 + I(age^2) + I(dur^2))
summary(model_test_1)
vif(model_test_1)
#R^2 = 0.1488
#р - ухудшился
#vif <= 3 

model_test_1 = lm(data = data3, salary~ age + sex + r_educ + status1 + dur + wed + wed2 + wed3 + I(dur^2))
summary(model_test_1)
vif(model_test_1)
#R^2 = 0.1345
#р - ухудшился
#vif <= 3

model_test_1 = lm(data = data3, salary~ age + sex + r_educ + status1 + dur + wed + wed2 + wed3 + I(age^2))
summary(model_test_1)
vif(model_test_1)
#R^2 = 0.1484
#р - чуть-чуть хуже, чем у исходной модели
#vif <= 3

model_test_1 = lm(data = data3, salary~ age + sex + r_educ + status1 + dur + wed + wed2 + wed3 + I(log(age)) + I(log(dur)))
summary(model_test_1)
vif(model_test_1)
#R^2 = 0.1687
#р - ухудшился
#vif <= 7

model_test_1 = lm(data = data3, salary~ age + sex + r_educ + status1 + dur + wed + wed2 + wed3 + I(log(dur)))
summary(model_test_1)
vif(model_test_1)
#R^2 = 0.1407
#р - хуже, чем у начальной модели, но лучше, чем у остальных моделей со степенями и логарифмами
#vif <= 5

model_test_1 = lm(data = data3, salary~ age + sex + r_educ + status1 + dur + wed + wed2 + wed3 + I(log(age)))
summary(model_test_1)
vif(model_test_1)
#R^2 = 0.1596
#р - ухудшился
#vif <= 7

#Итог: лучшая модель это salary~ age + sex + r_educ + status1 + dur + wed + wed2 + wed3 + I(log(dur))
#проверим модель на линейную зависимость параметров
modele_1 = lm(dur~I(log(dur)), data3)
modele_1
summary(modele_1) # R^2 =  0.8063 < 0.8, значит нет линейной зависимости и можно использовать в одной модели

modele_2 = lm(age~I(dur^2), data3)
modele_2
summary(modele_2) # R^2 =  3.001e-05 < 0.1 , значит нет линейной зависимости и можно использовать в одной модели

#Вывод: более высокую ЗП получают мужчины молодого возраста без высшего образования, работающие в областном центре , перерабатывающие, 
# не состоявшие в браке или вдовец или официально зарегистрированные, но не проживающие вместе.

#(Intercept)      age          sex       r_educ      status1          dur          wed         wed2         wed3    I(log(dur))  
#0.009378    -0.100804     0.452144    -0.030679    -0.154806     0.068537    -0.086875     0.143205     0.152724     0.056648    

#Ищем подмножества: "Женщины не замужем"
data4 = subset(data3, sex == 0)
data4

data5 = subset(data4, wed2 == 1)
data5

# Ищем подмножество: "женщины, живущие в городе, разведенные"
data6 = subset(data3, sex == 0)
data6

data7 = subset(data6, status1 == 1)
data7

data8 = subset(data7, wed2 == 1)
data8

#так как регрессор sex = const и wed2 = const, то уберем их из нашей модели, потому что строить зависимость от const не имеет смысла; т.к.wed = wed3 , то уберем wed3 из нашей модели.
model_subset = lm(data = data5, salary~age + r_educ + status1 + dur + wed)
summary(model_subset)
# R^2 = 0.08617
# Наивысшую зарплату получают женщины молодого возраста, без высшего образования, работающие не в городе, перерабатывающие и не состоявшие в браке

#так как регрессор sex = const и wed2 = const, status1 = const, то уберем их из нашей модели, потому что строить зависимость от const не имеет смысла; т.к.wed = wed3 , то уберем wed3 из нашей модели.
model_subset = lm(data = data8,salary~age + r_educ + dur + wed)
summary(model_subset)
# R^2 = 0.06726
# Наивысшую зарплату получают женщины молодого возраста, живущие в городе, разведенные или которые никогда не были в браке, без высшего образования и перерабатывающие


