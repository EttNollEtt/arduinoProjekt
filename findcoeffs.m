function coeffs = findcoeffs(degree, points)
N = degree;
m = length(points(:,1));
x = points(:,1);
y = points(:,2);
A = zeros(m,N+1);
for k = 1:N+1
    A(:,k)=x.^(N+1-k);
end;
disp(A)
disp(y)
c = A \ y
end