library("lmtest")
library("GGally")
library("car")

#������� 2 (������� ���� �� ������ ������ � �������) ������� ��������� ������������ ����-06-20

data = swiss
help(swiss)

# _1 - �� Education
modele_1 = lm(Agriculture~Education, data)
modele_1
summary(modele_1)
#�����:
# R^2 = 0.409 -> �������� ������ ����������, ����� ����� ������� �����������
# A = -1.51*ed + 67.24 -> ��� ���� ���� ������������� ���������, ��� ������ ����� ���������� ���������� �����
# ����� ��������� => ����� ������ ����������� ��������������
plot(modele_1) + abline(a = 67.24, b = -1.5, col = "red")


# _2 - �� catholic
modele_2 = lm(Agriculture~Catholic, data)
modele_2
summary(modele_2)
#R^2 = 0.16 -> ������ ����� - �� �������������
# ��� ������ ���������, ��� ������ ����� ���������� ���������� �����
# ����� ��������� => ����� ������ ����������� ��������������
plot(modele_2) + abline(a = 41.67, b = 0.21, col = "red")

# 515.79 - ������� �������
var(data$Agriculture) 
# 22.71 - ���
sd(data$Agriculture)
# 50.66 - ������� ��������
mean(data$Agriculture)

# 1739.29 - ����� ������� �������
var(data$Catholic)
#41.7 - ���
sd(data$Catholic)
# 41.14 - ������� ��������
mean(data$Catholic)

# 92.45 - ��������� ������� ��������
var(data$Education)
# 9.61 - ���
sd(data$Education)
# 10.98 - ������� ��������
mean(data$Education)
