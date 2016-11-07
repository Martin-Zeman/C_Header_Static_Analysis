//Testcase for using previously declared structs including nested structs with a higher degree of nesting. Also shows the effect of different alignment options.

struct A1
{
    char m1[3];
    double m2;
    char m3;
    char m4;
    struct Nested
    {
        char m1;
        double m2;
        struct Lowest
        {
            char m1;
            double m2;
        } low;
    } m4;
    
    struct Nested m5;
    
    struct Nested2
    {
        struct Lowest m7;
        char m1;
        double m2;
        struct Lowest2
        {
            char m1;
            double m2;
        } lo;
    } m6;
};

struct A2
{
    struct Lowest l;
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
//Size 144
//Padding 68
// struct A1
// {
//     char m1[3];//3
//     //5
//     double m2;//8
//     char m3;//1
//     //7
//     char m4;//1
//     //7
//     struct Nested
//     {
//         char m1;//1
//         //7
//         double m2;//8
//         struct Lowest
//         {
//             char m1;//1
//             //7
//             double m2;//8
//         } low;//Size 16, Padding 7
//     } m4;//Size 32, Padding 14
// 
//     struct Nested m5;//Size 32, Padding 14
 // 
//     struct Nested2
//     {
//         struct Lowest m7;//Size 16, Padding 7
//         char m1;//1
//         //7
//         double m2;//8
//         struct Lowest2
//         {
//             char m1;//1
//             //7
//             double m2;//8
//         } lo;//Size 16, Padding 7
//     } m6;//Size 48, Padding 21
// };
// 
//Size 40
//Padding 21
// struct A2
// {
//     struct Lowest l;//Size 16, Padding 7
//     char m1;//1
//     //7
//     double m2;//8
//     char m3;//1
//     //7
// };
// 
//Size 184
//Padding 89
// struct A3
// {
//     struct A1 S1;//Size 144, Padding 68
//     struct A2 S2;//Size 40, Padding 21
// };
//----------------------------------


//----------------------------------
//Memory alignment option = 4 bytes:
//Size 136
//Padding 60
// struct A1
// {
//     char m1[3];//3
//     //5
//     double m2;//8
//     char m3;//1
//     //3
//     char m4;//1
//     //3
//     struct Nested
//     {
//         char m1;//1
//         //7
//         double m2;//8
//         struct Lowest
//         {
//             char m1;//1
//             //7
//             double m2;//8
//         } low;//Size 16, Padding 7
//     } m4;//Size 32, Padding 14
// 
//     struct Nested m5;//Size 32, Padding 14
 // 
//     struct Nested2
//     {
//         struct Lowest m7;//Size 16, Padding 7
//         char m1;//1
//         //7
//         double m2;//8
//         struct Lowest2
//         {
//             char m1;//1
//             //7
//             double m2;//8
//         } lo;//Size 16, Padding 7
//     } m6;//Size 48, Padding 21
// };
// 
//Size 40
//Padding 21
// struct A2
// {
//     struct Lowest l;//Size 16, Padding 7
//     char m1;//1
//     //7
//     double m2;//8
//     char m3;//1
//     //7
// };
// 
//Size 176
//Padding 81
// struct A3
// {
//     struct A1 S1;//Size 136, Padding 60
//     struct A2 S2;//Size 40, Padding 21
// };
//----------------------------------


//----------------------------------
//Memory alignment option = 2 bytes:
//Size 136
//Padding 60
// struct A1
// {
//     char m1[3];//3
//     //5
//     double m2;//8
//     char m3;//1
//     //1
//     char m4;//1
//     //5
//     struct Nested
//     {
//         char m1;//1
//         //7
//         double m2;//8
//         struct Lowest
//         {
//             char m1;//1
//             //7
//             double m2;//8
//         } low;//Size 16, Padding 7
//     } m4;//Size 32, Padding 14
// 
//     struct Nested m5;//Size 32, Padding 14
 // 
//     struct Nested2
//     {
//         struct Lowest m7;//Size 16, Padding 7
//         char m1;//1
//         //7
//         double m2;//8
//         struct Lowest2
//         {
//             char m1;//1
//             //7
//             double m2;//8
//         } lo;//Size 16, Padding 7
//     } m6;//Size 48, Padding 21
// };
// 
//Size 40
//Padding 21
// struct A2
// {
//     struct Lowest l;//Size 16, Padding 7
//     char m1;//1
//     //7
//     double m2;//8
//     char m3;//1
//     //7
// };
// 
//Size 176
//Padding 81
// struct A3
// {
//     struct A1 S1;//Size 136, Padding 60
//     struct A2 S2;//Size 40, Padding 21
// };
//----------------------------------