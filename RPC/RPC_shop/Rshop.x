struct inputVec{
	char Fname;
	int quantity;
};

program SHOP_CLIENT{
	version ADD_VERS{
	string buyFruit(inputVec)=1;
	}=1;
}=0x12345000;