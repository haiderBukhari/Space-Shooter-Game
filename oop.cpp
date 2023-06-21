#include <iostream>
using namespace std;

class Item
{
private:
    string Name, ItemType;
    float unitPrices;
public:
    Item()
    {
        Name = ItemType = "Anonymous";
        unitPrices = 0;
    }
    void setter_name(string Name)
    {
        this->Name = Name;
    }
    void setter_item(string ItemType)
    {
        this->ItemType = ItemType;
    }
    void setter_price(float unitPrice)
    {
        this->unitPrices = unitPrice;
    }
    string getter_name()
    {
        return Name;
    }
    string getter_item()
    {
        return ItemType;
    }
    float getter_price()
    {
        return unitPrices;
    }
};
class Egg : public Item
{
private:
    int purchased_unit = 1;
    bool issalse = false, isgift = false;
public:
    Egg(int purchased_unit=0, float unitprice=0, bool issalse = false, bool isgift = false)
    {
        this->setter_name("Egg");
        this->setter_item("Food");
        this->setter_price(unitprice);
        this->purchased_unit = purchased_unit;
        this->isgift = isgift;
        this->issalse = issalse;
    }
    bool get_is_sale()
    {
        return issalse;
    }
    bool get_is_gift()
    {
        return isgift;
    }
    //float price() {}
    bool gift() { return isgift; }
};
class Bread : public Item
{
private:
    int purchased_unit = 1;
    bool issalse = false, isgift = false;

public:
    Bread(int purchased_unit=0, float unitprice=0, bool issalse = false, bool isgift = false)
    {
        this->setter_name("Bread");
        this->setter_item("Food");
        this->setter_price(unitprice);
        this->purchased_unit = purchased_unit;
        this->isgift = isgift;
        this->issalse = issalse;
    }
    bool get_is_sale()
    {
        return issalse;
    }
    bool get_is_gift()
    {
        return isgift;
    }
    //float price() {}
    bool gift() { return isgift; }
};
class Pens : public Item
{
private:
    int purchased_unit = 1;
    bool issalse = false, isgift = false;

public:
    Pens(int purchased_unit=0, float unitprice=0, bool issalse = false, bool isgift = false)
    {
        this->setter_name("Pens");
        this->setter_item("supplies");
        this->setter_price(unitprice);
        this->purchased_unit = purchased_unit;
        this->isgift = isgift;
        this->issalse = issalse;
    }
    //float price() {}
    bool gift() { return isgift; }
    bool get_is_sale()
    {
        return issalse;
    }
    bool get_is_gift()
    {
        return isgift;
    }
};
class socks : public Item
{
private:
    int purchased_unit = 1;
    bool issalse = false, isgift = false;

public:
    socks(int purchased_unit=0, float unitprice=0, bool issalse = false, bool isgift = false)
    {
        this->setter_name("socks");
        this->setter_item("clothes");
        this->setter_price(unitprice);
        this->purchased_unit = purchased_unit;
        this->isgift = isgift;
        this->issalse = issalse;
    }
    bool get_is_sale()
    {
        return issalse;
    }
    bool get_is_gift()
    {
        return isgift;
    }
    //float price() {}
    bool gift() { return isgift; }
};

class Cart
{
private:
    Item *items;
    static int total_items;
    int count = 0;
    bool arr[4] = {false};
    Egg egg;
    Bread bread;
    Pens pen;
    socks sock;
    bool *issale, *isgift;
public:
    Cart(){

    }
    int getTotalItems()
    {
        return total_items;
    }
    // bool Discount() {}
    //float price() {}
    void add()
    {
        Item *ij = new Item[count - 1];
        bool *issale1 = new bool[count - 1];
        bool *isgift1 = new bool[count - 1];
        for (int i = 0; i < count - 1; i++)
        {
            ij[i] = items[i];
            issale1[i] = issale[i];
            isgift1[i] = isgift[i];
        }
        delete[] items;
        delete[] issale;
        delete[] isgift;
        items = new Item[count];
        issale = new bool[count];
        isgift = new bool[count];
        for (int i = 0; i < count - 1; i++)
        {
            items[i] = ij[i];
            issale[i] = issale1[i];
            isgift[i] = isgift1[i];
        }
        delete[] ij;
        delete[] issale1;
        delete[] isgift1;
        if (arr[0] == true)
        {
            items[count - 1].setter_name(egg.getter_name());
            // cout<<egg.getter_price();
            items[count - 1].setter_price(egg.getter_price());
            items[count - 1].setter_item(egg.getter_item());
            issale[count - 1] = egg.get_is_sale();
            isgift[count - 1] = egg.get_is_gift();
        }
        else if (arr[1] == true)
        {
            items[count - 1].setter_name(bread.getter_name());
            // cout<<egg.getter_price();
            items[count - 1].setter_price(bread.getter_price());
            items[count - 1].setter_item(bread.getter_item());
            issale[count - 1] = bread.get_is_sale();
            isgift[count - 1] = bread.get_is_gift();
        }
        for (int i = 0; i < 4; i++)
        {
            arr[i] = false;
        }
    }
    void operator+=(Egg sk)
    {
        egg = sk;
        count++;
        arr[0] = true;
        add();
    }
    void operator+=(Bread sk)
    {
        count++;
        bread = sk;
        arr[1] = true;
        add();
    }
    void operator+=(Pens sk)
    {
        pen = sk;
        count++;
        arr[2] = true;
        add();
    }
    void operator+=(socks sk)
    {
        count++;
        sock = sk;
        arr[3] = true;
        add();
    }
    void operator-=(socks *sk)
    {
        count--;
    }
    void operator-=(Pens *sk)
    {
        count--;
    }
    void operator-=(Bread *sk)
    {
        count--;
    }
    void operator-=(Egg *sk)
    {
        count--;
    }
    void display(){
        for(int i=0; i<count; i++){
            cout<<items[i].getter_name()<<' ';
            cout<<items[i].getter_item()<<' ';
            cout<<items[i].getter_price()<<' ';
            cout<<endl;
        }
    }
};
int Cart::total_items;

int main()
{
    Bread p1(12, 3);
    Egg p2(15, 1, true);
    socks p3(20, 2.0, true, true);
    Cart c1;
    c1 += p1; // add bread to cart
    c1 += p1;
    c1 += p2; // add eggs to cart
    c1 += p3;
    // cout<<"Byyy";
    c1.display();
}
