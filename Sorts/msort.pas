var c:integer; d:array[1..10] of integer;
procedure msort(a:array of integer; n:integer);
var t,m,k:integer; b:array[0..1000,0..1000] of integer;
        begin
        t:=0; m:=0; k:=0;
                repeat
                inc(t);
                if m<a[t] then m:=a[t];
                if a[t]=a[t+1] then inc(k)
                until t=n;
        if k=n then exit;
        while (m div 10)>10 do
                m:= m div 10;
        m:=m-c;
                repeat
                b[a[t] div trunc(round(exp(ln(10)*m))),b[a[t] div trunc(round(exp(ln(10)*m))),1000]]:=a[t];
                b[a[t] div trunc(round(exp(ln(10)*m))),b[a[t] div trunc(round(exp(ln(10)*m))),1000]+1]:=-1;
                inc(b[a[t] div trunc(round(exp(ln(10)*m))),1000]);
                dec(t)
                until t=0;
        inc(c);
        while t<=n do
                begin
                inc(t);
                if b[t,1000]>1 then msort(b[t],b[t,1000])
                end;
        t:=0;
                repeat
                inc(t); k:=0;
                        repeat
                        if b[t,k]<>-1 then a[t]:=b[t,k] else break
                        until b[t,k]=-1;
                until t=n;
        end;
begin
for c:=1 to 10 do
        d[c]:=random(10);
msort(d,c);
for c:=1 to 10 do
        write(d[c])
end.
