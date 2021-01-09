/*The IDL File  --- name IDL.x*/

/*Structure to hold the 2 values to be used in computation*/

struct values{
    float num1;
    float num2;
    char operation;
};

/*Programme, version and procedure definition*/

program COMPUTE{
    version COMPUTE_VERS{
        float ADD(values)=1;
        float SUB(values)=2;
		float MUL(values)=3;
		float DIV(values)=4;
        float MOD(values)=5;
        float LOG(values)=6;
		float COS(values)=7;
		float SIN(values)=8;
        float TAN(values)=9;
        float EXP(values)=10;
		float SINH(values)=11;
		float TANH(values)=12;
        float COSH(values)=13;
        float POW(values)=14;
		float SQRT(values)=15;		
    } = 6; 

} = 124; 

/*
values ---> This is the name of the data structure to send the parameters of the computation to the server.

COMPUTE ---> This is the name of the programme.

COMPUTE_VERS ---> This is the name of the programme version.

ADD(values) ---> This is one of the methods that we are going to call remotely. The data structure containing the 2 operands and the operation to perform is given as parameter to the remote method. This is similar for the other methods givenhere as well.

You can see that at the end of each method and the programme and version, we have given some numbers. These numbers are used to uniquely identify each entity. You can give any number that you like here. 

*/
