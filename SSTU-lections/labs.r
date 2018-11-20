help(seq)
x1 <- seq(0, 1, length.out = 11) 
x1 <- seq(stats::rnorm(20)) 
x2 <- seq(1, 9, by = 2) 
x3 <- seq(1, 9, by = pi) 
x4 <- seq(1, 6, by = 3) 
x5 <- seq(1.575, 5.125, by = 0.05) 
x6 <- seq(17) 
save.image("file.RData")
rm(list=ls())
load("file.RData") 

help(matrix) 
help(solve)
?("%*%")
A <- (matrix(data = rnorm (100, mean = 50, sd = 30), nrow = 10, ncol = 10))
X <- seq(10)
V <- A*X
B <- A%*%X
solve(A,B) 
 
HousePrice <- read.table(file="houses.data") 
HousePrice1 <- read.table(file="houses1.data", header = TRUE) 
HP <- edit(HousePrice) 
write.table(HP, file="myframe.txt", quote = FALSE, row.names = FALSE) 
HousePrice$Rooms 
HousePrice1$Rooms 
HP$Rooms

T <- c(rnorm (100, mean = 50, sd = 30))
png(filename="1.png")
plot(T)
png(filename="2.png") 
plot(sort(T))
png(filename="3.png") 
hist(T)
png(filename="4.png") 
plot(density(T))
png(filename="5.png") 
hist(T) 
rug(T)
dev.off()
cars
plot(cars)
plot(sin, 0, 2*pi)
plot(cos, 0, 2*pi)
plot(exp, 0, 5)
plot(log, 0, 10)


# a 2-dimensional example
x <- rbind(matrix(rnorm(100, sd = 0.3), ncol = 2),
matrix(rnorm(100, mean = 1, sd = 0.3), ncol = 2))
colnames(x) <- c("x", "y")
(cl<- kmeans(x, 2))
plot(x, col = cl$cluster)
points(cl$centers, col = 1:2, pch = 8, cex = 2)

(cl<- kmeans(x, 3))
png(filename="1.png")
plot(x, col = cl$cluster)
points(cl$centers, col = 1:2, pch = 8, cex = 2)

data <- cbind(iris$Petal.Length, iris$Petal.Width)

x <- data
colnames(x) <- c("x", "y")
(cl<- kmeans(x, 3))
png(filename="2.png")
plot(x, col = cl$cluster)
points(cl$centers, col = 1:3, pch = 8, cex = 2)
dev.off()

mydata<-data
wss<-(nrow(mydata)-1)*sum(apply(mydata,2,var))
for(i in 2:15)wss[i]<-sum(kmeans(mydata, centers=i)$withinss)
plot(1:15, wss, type="b", xlab="Number of Clusters",
ylab="Within groups sum of squares",
main="Assessing the Optimal Number of Clusters with the Elbow Method",
pch=20, cex=2)


