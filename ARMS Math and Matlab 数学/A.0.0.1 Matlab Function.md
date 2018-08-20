# 
```matlab
% rc2d.m
function D = rc2d(sz, metrics)
r = sz(1);
c = sz(1);
x = 0:c-1;
y = 0:r-1;
idx = find(x>c/2);
x(idx) = x(idx)-c;
idx = find(y>r/2);
y(idx) = y(idx)-r;

X = fftshift(repmat(x,r,1));
Y = fftshift(repmat(y',1,c));

switch lower(metrics)
    case 'euclidean'    % 欧氏距离 DE[(i,j),(h,k)] = sqrt((i-h)^2, (j-k)^2)
    D = sqrt(X.^2+Y.^2);
    case 'cityblock'    % 城市街区距离 D4[(i,j),(h,k)] = |i-h|+|j-k|
    D = abs(X) + abx(Y);
    case 'chessboard'   % 棋盘距离 D8[(i,j),(h,k)] = max{|i-h|, |j-k|}
    D = max(abs(X), abs(Y));
end

return;
```

```matlab
% demo.m
imsize = [50, 50];
metrics = {'euclidean', 'cityblock', 'chessboard'};
for i = 1:length(metrics)
    D = rc2d(imsize, metrics{i});
    figure(i);
    clf;
    mesh(D);
    titile(metrics{i});
```