library("lmtest")
library("GGally")
library("car")

data = swiss
help(swiss)

#Вариант 2 Бундуки Владислав КМБО-06-20

#Объясняемая переменная Agriculture , регрессоры: Fertility, Education, Catholic
#Используем лучшую модель, основываясь на результате работы 2.1 : 
#"Agriculture ~ I(Fertility^2), I(Education^2), I(Catholic^2), I(Fertility*Education), I(Fertility*Education*Catholic)"
model = lm(Agriculture ~ I(Fertility^2)+ I(Education^2)+ I(Catholic^2)+ I(Fertility*Education)+ I(Fertility*Education*Catholic), data)
model
summary(model)
#Agriculture = 7.919e+01 + (-3.195e-03)*Fertility^2 + (-8.119e-03)*Edu^2 + (2.724e-03)Cat^2 + (-2.640e-02)Fertility*Education +(-6.148e-05)Fertility * Education * Catholic
#R^2 =  0.5971

# 43 наблюдений и оценивалось 4 коэффициента: 41 - 6 = 35 степени свободы;

#Оценим доверительные интервалы для Agriculture:

# a) Доверительный интервал для Fertility^2
Std_Err = 1.952e-03
# Критерий Стьюдента: 95%, 35 степени свободы
t_critical = qt(0.975, df = 35) # ~2.03
model$coefficients[2] - t_critical * Std_Err
model$coefficients[2] + t_critical * Std_Err

# Доверительный интервал для Fertility = [model$coefficients[2] - t_critical * Std_Err , model$coefficients[2] + t_critical * Std_Err]
# [-0.007157706 ,  0.0007678357]  -> коэффициент может быть равным 0


# Проверка:
confint(model, level = 0.95)
#                                       2.5 %          97.5 %
#(Intercept)                          57.8162199031 1.005651e+02
#I(Fertility^2)                      -0.0071360925  7.462226e-04
#I(Education^2)                      -0.0259326469  9.695019e-03
#I(Catholic^2)                        0.0005238842  4.925086e-03
#I(Fertility * Education)            -0.0458579729 -6.936649e-03
#I(Fertility * Education * Catholic) -0.0003922415  2.692765e-04

# б) Доверительный интервал для Education^2
Std_Err = 8.821e-03
# Критерий Стьюдента: 95%, 35 степени свободы
model$coefficients[3] - t_critical * Std_Err
model$coefficients[3] + t_critical * Std_Err

# Доверительный интервал для Education = [model$coefficients[3] - t_critical * Std_Err , model$coefficients[3] + t_critical * Std_Err]
# [-0.0260264 ,  0.009788768] -> коэффициент может быть равным 0


# в) Доверительный интервал для Catholic^2
Std_Err = 1.090e-03
# Критерий Стьюдента: 95%, 35 степени свободы
model$coefficients[4] - t_critical * Std_Err
model$coefficients[4] + t_critical * Std_Err

# Доверительный интервал для Catholic = [model$coefficients[4] - t_critical * Std_Err , model$coefficients[4] + t_critical * Std_Err]
# [0.0005116675 ,  0.004937303] -> коэффициент не может быть равным 0

# г) доверительный интервал для Fertility * Education:
Std_Err = 9.636e-03
# Критерий Стьюдента: 95%, 35 степени свободы
model$coefficients[5] - t_critical * Std_Err
model$coefficients[5] + t_critical * Std_Err

# Доверительный интервал для Fertility * Education = [model$coefficients[5] - t_critical * Std_Err , model$coefficients[5] + t_critical * Std_Err]
# [-0.04595943 ,  -0.006835191] -> коэффициент не может быть равным 0

# д) доверительный интервал для Fertility * Education * Catholic:
Std_Err = 1.638e-04
# Критерий Стьюдента: 95%, 35 степени свободы
model$coefficients[6] - t_critical * Std_Err
model$coefficients[6] + t_critical * Std_Err

# Доверительный интервал для Fertility * Education * Catholic = [model$coefficients[6] - t_critical * Std_Err , model$coefficients[6] + t_critical * Std_Err]
# [-0.0003940142 ,  0.0002710492] -> коэффициент может быть равным 0

# е) доверительный интервал для свободного коэф:
Std_Err = 1.058e+01
# Критерий Стьюдента: 95%, 35 степени свободы
model$coefficients[1] - t_critical * Std_Err
model$coefficients[1] + t_critical * Std_Err

# Доверительный интервал для Intercept = [model$coefficients[1] - t_critical * Std_Err , model$coefficients[1] + t_critical * Std_Err]
# [57.71211 ,  100.6692] -> коэффициент не может быть равным 0

# Вывод: Поскольку 0 попадает в доверительный интервал регрессоров => не все регрессоры связаны с объясняемой переменной.

#Построим доверительный интервал для прогноза (Объясняемая переменная: Agriculture, регрессоры: Fertility , Education , Catholic )
model = lm(Agriculture ~ I(Fertility^2)+ I(Education^2)+ I(Catholic^2)+ I(Fertility*Education)+ I(Fertility*Education*Catholic), data)
model
summary(model)
#Agriculture = 7.919e+01 + (-3.195e-03)*Fertility^2 + (-8.119e-03)*Edu^2 + (2.724e-03)Cat^2 + (-2.640e-02)Fertility*Education +(-6.148e-05)Fertility * Education * Catholic

new.data = data.frame(Fertility = 15, Education = 15, Catholic = 30)

predict(model, new.data, interval = "confidence")
# fit      lwr      upr
# 72.74269 53.96525 91.52014

# Вывод: Прогноз модели оценивается как 72.74269;
# Доверительный интервал для свободного коэффициентa = [53.96525,91.52014]
