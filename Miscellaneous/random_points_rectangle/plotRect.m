function plotRect(A)

xx = [A(1), A(1)+A(3)];
xy1 = [A(1), A(1)];
xy2 = [A(1)+A(3), A(1)+A(3)];
yy = [A(2), A(2)+A(4)];
yx1 = [A(2), A(2)];
yx2 = [A(2)+A(4), A(2)+A(4)];

X = [xx xy2 fliplr(xx) xy1];
Y = [yx1 yy yx2 fliplr(yy)];
plot(X, Y, '-o');