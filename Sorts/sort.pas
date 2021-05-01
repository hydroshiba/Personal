//Variables

var
  matx: array[0..100000000]of longint; x, t: longint;

//Sort procedure

procedure sort(n: longint);
var
  temp, temp2: longint; b: array[0..100000000]of longint;

begin
  //Make all values 0
  temp := 0;
  repeat
    inc(temp);
    b[temp] := 0
  until temp = 100000000;

  //Sorting
  temp := 0;
  repeat
    inc(b[matx[temp]]);
    inc(temp)
  until temp = n;

  //Assign sorted values to main array
  temp := 0; temp2 := 0;
  repeat
    repeat
      if b[temp] = 0 then break;
      dec(b[temp]);
      matx[temp2] := temp;
      inc(temp2)
    until b[temp] = 0;
    inc(temp)
  until temp2 >= n
end;

//Main program

begin
  read(x);
  for t := 1 to x do
    matx[t - 1] := random(x);
  sort(x);
  for t := 1 to x do
    writeln(matx[t - 1], ' ')
end.
