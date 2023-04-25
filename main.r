library(tidyverse)
library(sqldf)
library(ggplot2)

data_csv <- read.csv("cpp_write.csv")

# 天賦的正態分佈
show(ggplot(data = data_csv, aes(x = talent)) + ggtitle("正態分佈") + geom_histogram(binwidth = 0.01, fill = "white", colour = "black"))

# 資產分配
show(ggplot(data = data_csv, aes(x = wealth)) + ggtitle("資產分配") + geom_histogram(binwidth = 100, fill = "white", colour = "black") + scale_y_continuous(trans = "log10")  )

# 帕雷托法則(Pareto Principle，八二法則)
sum(sqldf("SELECT wealth FROM data_csv ORDER BY wealth DESC LIMIT (SELECT 0.20 * COUNT(*) FROM data_csv)")) / (sqldf("SELECT SUM(wealth) FROM data_csv"))

sum(sqldf("SELECT wealth FROM data_csv ORDER BY wealth LIMIT (SELECT 0.80 * COUNT(*) FROM data_csv)")) / (sqldf("SELECT SUM(wealth) FROM data_csv"))

# 天賦的財富分配 將x軸數值轉化成log10
show(ggplot(data = data_csv, aes(x = wealth, y = talent)) + ggtitle("天賦的財富分配_1") + geom_point() + scale_x_continuous(trans = "log10") )

show(ggplot(data = data_csv, aes(x = talent, y = wealth)) + ggtitle("天賦的財富分配_2") + geom_point())

# 運氣的財富分配
show(ggplot(data = data_csv, aes(x = wealth, y = lucky_cnt)) + ggtitle("運氣的財富分配") + geom_point() + scale_x_continuous(trans = "log10") )

# 不幸的財富分配
show(ggplot(data = data_csv, aes(x = wealth, y = unlucky_cnt)) + ggtitle("不幸的財富分配") + geom_point() + scale_x_continuous(trans = "log10") )