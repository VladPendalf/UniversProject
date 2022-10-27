library("lmtest")
library("GGally")
library("car")

#Вариант 2 (Вариант взял по своему номеру в журнале) Бундуки Владислав Вячеславович КМБО-06-20

data = swiss
help(swiss)

# _1 - от Education
modele_1 = lm(Agriculture~Education, data)
modele_1
summary(modele_1)
#Вывод:
# R^2 = 0.409 -> довольно низкий показатель, нужны более сложные зависимости
# A = -1.51*ed + 67.24 -> чем выше доля образованного населения, тем меньше людей занимаются обработкой земли
# Много звездочек => очень четкая зависимость проглядывается
plot(modele_1) + abline(a = 67.24, b = -1.5, col = "red")


# _2 - от catholic
modele_2 = lm(Agriculture~Catholic, data)
modele_2
summary(modele_2)
#R^2 = 0.16 -> делать вывод - не целесообразно
# чем больше Католиков, тем больше людей занимаются обработкой земли
# Много звездочек => очень четкая зависимость проглядывается
plot(modele_2) + abline(a = 41.67, b = 0.21, col = "red")

# 515.79 - большой разброс
var(data$Agriculture) 
# 22.71 - СКО
sd(data$Agriculture)
# 50.66 - среднее значение
mean(data$Agriculture)

# 1739.29 - ОЧЕНЬ БОЛЬШОЙ РАЗБРОС
var(data$Catholic)
#41.7 - СКО
sd(data$Catholic)
# 41.14 - среднее значение
mean(data$Catholic)

# 92.45 - маленький разброс значений
var(data$Education)
# 9.61 - СКО
sd(data$Education)
# 10.98 - среднее значение
mean(data$Education)
