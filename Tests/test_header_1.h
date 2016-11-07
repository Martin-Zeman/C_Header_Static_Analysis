//Simple testcase with little to no padding at all.

struct A1
{
    int m1;
    int m2;
    double m3;
    double m4;
};

//----------------------------------
//Memory alignment option = 8 bytes:
//Size 32
//Padding 8
// struct A1
// {
//     int m1;//4
//	   //4
//     int m2;//4
//	   //4
//     double m3;//8
//     double m4;//8
// };
//----------------------------------


//----------------------------------
//Memory alignment option = 4 bytes:
//Size 24
//Padding 0
// struct A1
// {
//     int m1;//4
//     int m2;//4
//     double m3;//8
//     double m4;//8
// };
//----------------------------------


//----------------------------------
//Memory alignment option = 2 bytes:
//Size 24
//Padding 0
// struct A1
// {
//     int m1;//4
//     int m2;//4
//     double m3;//8
//     double m4;//8
// };
//----------------------------------
