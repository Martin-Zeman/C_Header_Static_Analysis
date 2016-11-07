//Testcase for using previously declared structs. This testcase is alignment option invariant.

struct A1
{
    char m1[3];
    double m2;
    char m3;
};

struct A2
{
    char m1;
    double m2;
    char m3;
};

struct A3
{
    struct A1 S1;
    struct A2 S2;
};

//----------------------------------
//Memory alignment option = 8 bytes:
//Size 24
//Padding 12
// struct A1
// {
//     char m1[3];//3
//     //5
//     double m2;//8
//     char m3;//1
//     //7
// };
// 
//Size 24
//Padding 14
// struct A2
// {
//     char m1;//1
//     //7
//     double m2;//8
//     char m3;//1
//     //7
// };
// 
//Size 48
//Padding 26
// struct A3
// {
//     struct A1 S1;//Size 24, Padding 12
//     struct A2 S2;//Size 24, Padding 14
// };
//----------------------------------


//----------------------------------
//Memory alignment option = 4 bytes:
//Size 24
//Padding 12
// struct A1
// {
//     char m1[3];//3
//     //5
//     double m2;//8
//     char m3;//1
//     //7
// };
// 
//Size 24
//Padding 14
// struct A2
// {
//     char m1;//1
//     //7
//     double m2;//8
//     char m3;//1
//     //7
// };
// 
//Size 48
//Padding 26
// struct A3
// {
//     struct A1 S1;//Size 24, Padding 12
//     struct A2 S2;//Size 24, Padding 14
// };
//----------------------------------


//----------------------------------
//Memory alignment option = 2 bytes:
//Size 24
//Padding 12
// struct A1
// {
//     char m1[3];//3
//     //5
//     double m2;//8
//     char m3;//1
//     //7
// };
// 
//Size 24
//Padding 14
// struct A2
// {
//     char m1;//1
//     //7
//     double m2;//8
//     char m3;//1
//     //7
// };
// 
//Size 48
//Padding 26
// struct A3
// {
//     struct A1 S1;//Size 24, Padding 12
//     struct A2 S2;//Size 24, Padding 14
// };
//----------------------------------