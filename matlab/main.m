

k = 1;
c = 0.1;
m1 = 1;
m2 = 1;


A = [0, 1, 0, 0;
     -2*k/m1, -2*c/m1, k/m1, c/m1;
     0, 0, 0, 1;
     k/m2, c/m2, -k/m2, -c/m2];

B = [0; 1/m1; 0; 0];

% C = diag([1,0,1,0]);
C = eye(4);

D = zeros(4,1);


% lqr
Ce = [1, 0, 0, 0];

Ae = [ A, zeros(4,1);
      -Ce, 0];

Be = [B;0];

Q  = diag([10,200,1,10,10]);
R  = 1.0;

Klqr  = lqr(Ae, Be, Q, R)

K  = Klqr(1:4);
Ke = Klqr(5);

sim('model');