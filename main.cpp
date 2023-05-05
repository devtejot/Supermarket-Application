#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct item
{
    long long item_Id ; 
    int name ;
    float rate ;
    int quantity ;
    item *next ;
};

struct customerstruct
{
    long long Customer_Id;
    int name;
    int points;
    customerstruct *next;
};

int Trasaction_Id = 1;
int csize ;
customerstruct *customer_list;
int isize ;
item *item_list;


//--------------------------------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------------------------------

class Customer
{
    public :
    int csize ;
    customerstruct *customer_list;

    //constructor
    Customer()
    {
        csize = 10 ;
        customer_list = new customerstruct[csize];
        for(int i = 0 ; i<csize ; i++ )       
        {
            customer_list[i].Customer_Id = 0; 
        }
    }

    //function to add new customer in teh customer list 
    void Add_Customer( long long id , long n , long p)
    {
        int index = id % csize ;
        if(customer_list[index].Customer_Id == 0)
        {
            customer_list[index].Customer_Id = id;
            customer_list[index].name = n;
            customer_list[index].points = p;
            customer_list[index].next = NULL;
        }
        else 
        {
            customerstruct *tmp = new customerstruct();
            tmp=&customer_list[index];
            customerstruct *t = new customerstruct();
            t->Customer_Id = id;
            t->name = n;
            t->points = p;
            t->next=NULL;
            while(tmp->next != NULL )
            {
                tmp = tmp->next;
            }
            tmp->next = t;
        }
    }

    int Search_Customer(long long id)
    {   
        int index = id % csize ;
        customerstruct *tmp = &customer_list[index] ;
        while(tmp != NULL)
        {
            if(tmp->Customer_Id == id)
            {
                return 1;
            }
            tmp = tmp->next ;
        }

        return 0;
    }

    void Update_Points(long long id , long p , Customer Z)
    {
        int index = id % csize ;
        customerstruct *tmp = &Z.customer_list[index] ;
        while(tmp != NULL)
        {
            if(tmp->Customer_Id == id)
            {
                tmp->points = tmp->points + p;
                break ;
            }
            tmp = tmp->next ;
        }
    }

    void Diplay_Points()
    {
       int i ;
        for(i=0 ; i<10 ; i++)
        {
            customerstruct *tmp = &customer_list[i];
            while(tmp != NULL)
            {
                cout<<tmp->points;
                if(tmp->next != NULL)
                {
                    cout<<"--->";
                }
                tmp = tmp->next;
            }
            cout<<endl;
        }
    }

};
//-------------------------------------------------------------------------------------------------------------------------------------------
class Inventory 
{
    private :
    

    

    //function to add the item in the item list
    void Add_Item( long long id , int n , float r , int q)
    {
        
        int index = id % isize ;
    
        if(item_list[index].item_Id == 0)
        {
            item_list[index].item_Id = id;
            item_list[index].name = n;
            item_list[index].rate = r;
            item_list[index].quantity = q;
            item_list[index].next = NULL;
        }
        else 
        {
            item *tmp = new item();
            tmp=&item_list[index];
            item *t = new item();
            t->item_Id = id;
            t->name = n;
            t->rate = r;
            t->quantity = q;
            t->next=NULL;
            while(tmp->next != NULL )
            {
                tmp = tmp->next;
            }
            tmp->next = t;
        }
    }

    void Display()
    {
        int i ;
        for(i=0 ; i<10 ; i++)
        {
            item *tmp = &item_list[i];
            while(tmp != NULL)
            {
                cout<<tmp->item_Id;
                if(tmp->next != NULL)
                {
                    cout<<"--->";
                }
                tmp = tmp->next;
            }
            cout<<endl;
        }
    }

    //function to update info about the item in the item list 
    void Update_Item(long long id , long q)
    {
        int index = id % isize ;
        item *tmp = new item();
        tmp = &item_list[index];
        while(tmp != NULL)
        {
            if(tmp->item_Id == id)
            {
                tmp->quantity = tmp->quantity - q;
                break ;
            }
            tmp=tmp->next;
        }
        if(tmp==NULL)
        {
            cout<<"Item Not Found"<<endl;
        }
    }
    
    //function to delete the item from the item list
    void Delelte_Item(long long id)
    {
        int index = id % isize ;
        item *tmp = new item();
        item *prev = new item();
        tmp = &item_list[index];
        while(tmp != NULL)
        {
            if(tmp->item_Id == id)
            {
                prev->next = tmp->next;
                break ;
            }
            prev = tmp;
            tmp = tmp->next;
        }
        if(tmp==NULL)
        {
            cout<<"Item Not Found"<<endl;
        }
    }

    
    

    
    public:
    friend class Manager;
    
    long isize ;
    item *item_list;
    
    Inventory()
    {
        isize = 10 ;
        item_list = new item[isize];
        for(int i = 0 ; i<isize ; i++ )       
        {
            item_list[i].item_Id = 0; 
        }
    }
    
    //function to update the stock
    
    void Update_Stock(long long id , float r , long q)
    {
        int index = id % isize ;
        item *tmp = new item();
        tmp = &item_list[index];
        while(tmp != NULL)
        {
            if(tmp->item_Id == id)
            {
                tmp->rate = r ;
                tmp->quantity = q;
                break ;
            }
            tmp=tmp->next;
        }

    }
	//function to get product info
    void Get_Product_Info(long long id)
    {
        int index = id % isize ;
        item *tmp = new item();
        tmp = &item_list[index];
        while(tmp != NULL)
        {
            if(tmp->item_Id == id)
            {
                cout<<tmp->item_Id<<" , "<<tmp->name<<" , "<<tmp->rate<<" , "<<tmp->quantity<<endl;
                break ;
            }
            tmp = tmp->next;
        }
        if(tmp==NULL)
        {
           cout<<"Item Not Found"<<endl;
        }
    }

};


//--------------------------------------------------------------------------------------------------------------------------------------------
int Transaction_Id = 0;
class Billing : public Customer , public Inventory
{
    public :
    int i=0;
    long long Customer_id;
    long long Shopping_List[3][4];
    int amount;

    //function to add items in the item list
    void Buy_Item(Inventory X , long long id ,long long q)
    {
        int index = id % isize ;
        item *tmp = &X.item_list[index];
        while(tmp != NULL)
        {
            if(tmp->item_Id == id)
            {
                if(q <= tmp->quantity)
                {
                    Shopping_List[i][0] = tmp->item_Id;
                    Shopping_List[i][1] = tmp->name;
                    Shopping_List[i][2] = tmp->rate;
                    Shopping_List[i][3] = q;
                }
                else
                {
                    cout<<"Current quantity of item available is : "<<tmp->quantity<<endl;
                }
                
                break ;
            }
            
            tmp = tmp->next;
        }
        
        if(tmp==NULL)
        {
            cout<<"Item Not Found"<<endl;
        }
        i++;
    }

    //function to cancel item in the item list
    void Cancel_Item(long long id)
    {
        int j;
        for(int j=0 ; j<=i ; j++)
        {
            if(id==Shopping_List[j][0])
            {
                break;
            }
        }
        
        for(j ; j<i ; j++)
        {
            Shopping_List[j][0]=Shopping_List[j+1][0];
            Shopping_List[j][1]=Shopping_List[j+1][1];
            Shopping_List[j][2]=Shopping_List[j+1][2];
            Shopping_List[j][3]=Shopping_List[j+1][3];
        }
        i--;
    }

    //function to display item list
    void Display()
    {
        cout<<"Item Id         Name    Rate    Quantity    Amount"<<endl;
        for(int j=0 ; j<i ; j++)
        {
            cout<<Shopping_List[j][0]<<"     "<<Shopping_List[j][1]<<"     "<<Shopping_List[j][2]<<"     "<<Shopping_List[j][3]<<"          "<<(Shopping_List[j][2]*Shopping_List[j][3])<<endl;
        }
    }

    //function to display bill for final payment
    void Make_Payment(long long cid , Customer X , Inventory A)
    {
        long long customerid = assign_customer_id(cid , X);
        float totalamount=0;
        Transaction_Id++;
        cout<<"Transaction_Id : "<<Transaction_Id<<endl;
        cout<<"Customer_Id : "<<customerid<<endl;
        cout<<"Item Id         Name    Rate    Quantity    Amount"<<endl;
        for(int j=0 ; j<i ; j++)
        {
        	item *node = &A.item_list[Shopping_List[j][0]%isize];
            cout<<Shopping_List[j][0]<<"    "<<Shopping_List[j][1]<<"      "<<Shopping_List[j][2]<<"     "<<Shopping_List[j][3]<<"           "<<Shopping_List[j][2]*Shopping_List[j][3]<<endl;
            totalamount = totalamount + (Shopping_List[j][2]*Shopping_List[j][3]);
            A.Update_Stock(Shopping_List[j][0],Shopping_List[j][2],node->quantity-Shopping_List[j][3]);
        }
        cout<<"Total : "<<totalamount <<endl;
        Update_Points(cid , totalamount , X);
        
        cout<<endl;
        
    }

    //function to assign customer id if exists else add the customer to customer list
    long long assign_customer_id(long long id , Customer Y)
    {
        int i = Y.Search_Customer(id);
        if (i==0)
        {
            long n;
            cin>>n;
            Y.Add_Customer(id , n ,0);
        }
        return id;
    }

    void Add_Customers(Customer X , long long id , long n , long p)
    {
        X.Add_Customer(id,n,p);
    }
};

//--------------------------------------------------------------------------------------------------------------------------------------------

class Manager
{
    public:
    long Manager_Id ;
    int name;

    
    Manager(long long id , int n)
    {
        Manager_Id = id;
        name = n ;
    }

    void Print_Product_Info(long long id , Inventory X)
    {
        X.Get_Product_Info(id);
    }

    void Add_Product(Inventory& X , long long id , int n , float r , int q)
    {
        X.Add_Item(id , n , r , q);
    }

    void Update_Product(Inventory& X , long long id , float r , long q)
    {
        X.Update_Stock(id , r , q);
    }

    void Delete_Product(Inventory& X , long long id)
    {
        X.Delelte_Item(id);
    }

};

//--------------------------------------------------------------------------------------------------------------------------------------------

int main() 
{
    Manager M(201901022 , 1);
    Billing B1 ;
    Inventory I ;
    Customer C ;

    long long INVENTORY_DATASET[100][4] = 
    {
        {111100000001,1,100,20},{111100000002,2,110,20},{111100000003,3,120,20},{111100000004,4,130,20},{111100000005,5,140,20},{111100000006,6,150,20},{111100000007,7,160,20},{111100000008,8,170,20},{111100000009,9,180,20},{111100000010,10,190,20},
        {111100000011,11,200,20},{111100000012,12,210,20},{111100000013,13,220,20},{111100000014,14,230,20},{111100000015,15,240,20},{111100000016,16,250,20},{111100000017,17,260,20},{111100000018,18,270,20},{111100000019,19,280,20},{111100000020,20,290,20},
        {111100000021,21,300,20},{111100000022,22,310,20},{111100000023,23,320,20},{111100000024,24,330,20},{111100000025,25,340,20},{111100000026,26,350,20},{111100000027,27,360,20},{111100000028,28,370,20},{111100000029,29,380,20},{111100000030,30,390,20},
        {111100000031,31,400,20},{111100000032,32,410,20},{111100000033,33,420,20},{111100000034,34,430,20},{111100000035,35,440,20},{111100000036,36,450,20},{111100000037,37,460,20},{111100000038,38,470,20},{111100000039,39,480,20},{111100000040,40,490,20},
        {111100000041,41,500,20},{111100000042,42,510,20},{111100000043,43,520,20},{111100000044,44,530,20},{111100000045,45,540,20},{111100000046,46,550,20},{111100000047,47,560,20},{111100000048,48,570,20},{111100000049,49,580,20},{222200001111,50,590,20},
        {222200001114,51,600,20},{222200001117,52,610,20},{222200001120,53,620,20},{222200001123,54,630,20},{222200001126,55,640,20},{222200001129,56,650,20},{222200001132,57,660,20},{222200001135,58,670,20},{222200001138,59,680,20},{222200001141,60,690,20},
        {222200001144,61,700,20},{222200001147,62,710,20},{222200001150,63,720,20},{222200001153,64,730,20},{222200001156,65,740,20},{222200001159,66,750,20},{222200001162,67,760,20},{222200001165,68,770,20},{222200001168,69,780,20},{222200001171,70,790,20},
        {222200001174,71,800,20},{222200001177,72,810,20},{222200001180,73,820,20},{222200001183,74,830,20},{222200001186,75,840,20},{222200001189,76,850,20},{222200001192,77,860,20},{222200001195,78,870,20},{222200001198,79,880,20},{222200001201,80,890,20},
        {222200001204,81,900,20},{222200001207,82,910,20},{222200001210,83,920,20},{222200001213,84,930,20},{222200001216,85,940,20},{222200001219,86,950,20},{222200001222,87,960,20},{222200001225,88,970,20},{222200001228,89,980,20},{222200001231,90,990,20},
        {222200001234,91,1000,20},{222200001237,92,1010,20},{222200001240,93,1020,20},{222200001243,94,1030,20},{222200001246,95,1040,20},{222200001249,96,1050,20},{222200001252,97,1060,20},{222200001255,98,1070,20},{222200001258,99,1080,20},{222200001261,100,1090,20},
    };

    long long CUSTOMER_DATASET[100][3] = 
    {
        {9400000001,1,0},{9400000002,2,0},{9400000003,3,0},{9400000004,4,0},{9400000005,5,0},{9400000006,6,0},{9400000007,7,0},{9400000008,8,0},{9400000009,9,0},{9400000010,10,0},
        {9400000011,11,0},{9400000012,12,0},{9400000013,13,0},{9400000014,14,0},{9400000015,15,0},{9400000016,16,0},{9400000017,17,0},{9400000018,18,0},{9400000019,19,0},{9400000020,20,0},
        {9400000021,21,0},{9400000022,22,0},{9400000023,23,0},{9400000024,24,0},{9400000025,25,0},{9400000026,26,0},{9400000027,27,0},{9400000028,28,0},{9400000029,29,0},{9400000030,30,0},
        {9400000031,31,0},{9400000032,32,0},{9400000033,33,0},{9400000034,34,0},{9400000035,35,0},{9400000036,36,0},{9400000037,37,0},{9400000038,38,0},{9400000039,39,0},{9400000040,40,0},
        {9400000041,41,0},{9400000042,42,0},{9400000043,43,0},{9400000044,44,0},{9400000045,45,0},{9400000046,46,0},{9400000047,47,0},{9400000048,48,0},{9400000049,49,0},{9400000050,50,0},
        {9400000051,51,0},{9400000052,52,0},{9400000053,53,0},{9400000054,54,0},{9400000055,55,0},{9400000056,56,0},{9400000057,57,0},{9400000058,58,0},{9400000059,59,0},{9400000060,60,0},
        {9400000061,61,0},{9400000062,62,0},{9400000063,63,0},{9400000064,64,0},{9400000065,65,0},{9400000066,66,0},{9400000067,67,0},{9400000068,68,0},{9400000069,69,0},{9400000070,70,0},
        {9400000071,71,0},{9400000072,72,0},{9400000073,73,0},{9400000074,74,0},{9400000075,75,0},{9400000076,76,0},{9400000077,77,0},{9400000078,78,0},{9400000079,79,0},{9400000080,80,0},
        {9400000081,81,0},{9400000082,82,0},{9400000083,83,0},{9400000084,84,0},{9400000085,85,0},{9400000086,86,0},{9400000087,87,0},{9400000088,88,0},{9400000089,89,0},{9400000090,90,0},
        {9400000091,91,0},{9400000092,92,0},{9400000093,93,0},{9400000094,94,0},{9400000095,95,0},{9400000096,96,0},{9400000097,97,0},{9400000098,98,0},{9400000099,99,0},{9400000100,100,0},
    };
    
    int i=0;
    while(i<100)
    {
        M.Add_Product(I,INVENTORY_DATASET[i][0],INVENTORY_DATASET[i][1],INVENTORY_DATASET[i][2],INVENTORY_DATASET[i][3]);
        B1.Add_Customers(C,CUSTOMER_DATASET[i][0],CUSTOMER_DATASET[i][1],CUSTOMER_DATASET[i][2]);
        i++;
    }
    
    B1.Buy_Item(I,111100000011,3);
    B1.Buy_Item(I,222200001114,1);
    B1.Buy_Item(I,222200001234,12);
    B1.Make_Payment(9400000011,C,I);


    M.Print_Product_Info(111100000011,I);
    M.Print_Product_Info(222200001114,I);
    M.Print_Product_Info(222200001234,I);

    return 0;
}
