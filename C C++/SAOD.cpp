#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <string.h>
#include <conio.h>

using namespace std;

const int N = 4000;
int sym_count = 0;

struct Record
{
    char Name[30];
    union
    {
        short int Department;
        char Depart[2];
    };
    char Post[22];
    char Birthday[10];
};

struct Ochered
{
    Record record;
    Ochered* next;
};

string Output(const string& str)
{
    cout << str;
    cout << "\n> ";
    string ans;
    cin >> ans;
    return ans;
}

struct Vertex
{
    Record* data;
    Vertex* next;
    int bal;
    Vertex* left;
    Vertex* right;
};

bool VR = true;
bool HR = true;

Ochered* Load_base()
{
    ifstream file("testBase2.dat", ios::binary);
    if (!file.is_open())
    {
        return NULL;
    }

    Ochered* root = NULL;

    for (int i = 0; i < N; ++i)
    {
        Record record;
        file.read((char*)&record, sizeof(Record));
        root = new Ochered{ record, root };
    }

    file.close();
    return root;
}

void Print(Record* record, int i)
{
    cout << "|" << setw(4) << i << "|"
        << "  " << record->Name
        << "  " << setw(3) << record->Department
        << "  " << record->Post
        << "  " << record->Birthday << "\n";
}

void Menu_list(Record* ind_arr[], int n = N)
{
    int ind = 0;
    while (true)
    {
        cout << "Record  Name                    Department  Post                   Birth date\n";
        for (int i = 0; i < 20; i++)
        {
            Record* record = ind_arr[ind + i];
            Print(record, ind + i + 1);
        }
        string chose = Output("d: Next page\n"
            "a: Prev page\n"
            "e: Skip 10 next pages\n"
            "q: Skip 10 prev pages\n"
            "w: First page\n"
            "s: Last page\n"
            "z: Exit");
        
        char key= chose[0];
        
        if (key == 'd' || key == 'D') {
            ind += 20;
        }
        if (key == 'a' || key == 'A') {
            ind -= 20;
        }
        if (key == 'w' || key == 'W') {
            ind = 0;
        }
        if (key == 's' || key == 'S') {
            ind = n - 20;
        }
        if (key == 'q' || key == 'Q') {
            ind -= 200;
        }
        if (key == 'e' || key == 'E') {
            ind += 200;
        }
        if (key == 'z' || key == 'Z') {
            return;
        }

        if (ind < 0)
        {
            ind = 0;
        }
        else if (ind > n - 20)
        {
            ind = n - 20;
        }
    }
}

void Index_array(Record* arr[], Ochered* root, int n = N)
{
    Ochered* p = root;
    for (int i = 0; i < n; i++)
    {
        arr[i] = &(p->record);
        p = p->next;
    }
}

void Digital_Sort(Ochered*& head)
{
    int first_f = 2;
    int sec_f = 30;
    struct Queue
    {
        Ochered* tail;
        Ochered* head;
    } q[256];
    int L = first_f + sec_f;
    Ochered* p;

    for (int j = 0; j < L; j++)
    {
        for (auto& i : q)
        {
            i.tail = i.head = NULL;
        }
        while (head)
        {
            int x;
            if (j < sec_f)
            {
                x = 255 - abs(head->record.Name[L - j - 1 - first_f]);
            }
            else if (j < sec_f + first_f)
            {
                x = (unsigned char)head->record.Depart[L - j - 1];
            }
            p = q[x].tail;
            if (q[x].head == NULL)
                q[x].head = head;
            else
                p->next = head;

            p = q[x].tail = head;
            head = head->next;
            p->next = NULL;
        }
        int i;
        for (i = 0; i < 256; i++)
        {
            if (q[i].head != NULL)
                break;
        }
        head = q[i].head;
        p = q[i].tail;
        for (int y = i + 1; y < 256; y++)
        {
            if (q[y].head != NULL)
            {
                p->next = q[y].head;
                p = q[y].tail;
            }
        }
    }
}

int Quick(Record* arr[], int key)
{
    int L = 0;
    int R = N - 1;
    while (L < R)
    {
        int m = (L + R) / 2;
        if (arr[m]->Department < key)
        {
            L = m + 1;
        }
        else
        {
            R = m;
        }
    }
    if (arr[R]->Department == key)
    {
        return R;
    }
    return -1;
}

void Search(Record* arr[], int& ind, int& n)
{
    Ochered* head = nullptr, * tail = nullptr;
    int key;
    while (true)
    {
        try
        {
            key = stoi(Output("Input search key depatrment"));
            break;
        }
        catch (invalid_argument& exc)
        {
            cout << "Please input a number\n";
            continue;
        }
    }
    ind = Quick(arr, key);
    if (ind == -1)
    {
        cout << "Not found\n";
    }
    else
    {
        head = new Ochered{ *arr[ind], nullptr };
        tail = head;
        int i;
        for (i = ind + 1; i < 4000 && arr[i]->Department == key; ++i)
        {
            tail->next = new Ochered{ *arr[i], nullptr };
            tail = tail->next;
        }
        n = i - ind;
        auto find_arr = new Record * [n];
        Index_array(find_arr, head, n);
        Menu_list(find_arr, n);
        delete[] find_arr;
    }
}

int Сomparison(Record* a, Record* b) {
    char A[10];
    char B[10];
    strcpy(A, a->Birthday);
    strcpy(B, b->Birthday);
    int space_a= strchr(a->Birthday, ' ') - a->Birthday;
    int space_b = strchr(b->Birthday, ' ') - b->Birthday;

    int count = 0;
    if (space_a< space_b) {
        count = space_a;
    }
    else {
        count = space_b;
    }
    if (strncmp(A, B, count) > 0) {
        return 1;
    }
    if (strncmp(A, B, count) < 0) {
        return -1;
    }
    if (space_a> space_b) {
        return 1;
    }
    if (space_a< space_b) {
        return -1;
    }
    return 0;
}

void DBD(Record* x, Vertex*& p) {
    if (p == NULL) {
        p = new Vertex;
        p->data = x;
        p->bal = 0;
        p->next = NULL;
        p->left = NULL;
        p->right = NULL;
        VR = true;
    }
    else if (Сomparison(p->data, x) == 0) {
        DBD(x, p->next);
    }
    else if (Сomparison(p->data, x) > 0) {
        DBD(x, p->left);
        if (VR) {
            if (p->bal == 0) {
                Vertex* q = p->left;
                p->left = q->right;
                q->right = p;
                p = q;
                q->bal = 1;
                VR = 0;
                HR = 1;
            }
            else {
                p->bal = 0;
                VR = 1;
                HR = 0;
            }
        }
        else HR = 0;
    }
    else if (Сomparison(p->data, x) < 0) {
        DBD(x, p->right);
        if (VR) {
            p->bal = 1;
            HR = 1;
            VR = 0;
        }
        else if (HR) {
            if (p->bal == 1) {
                Vertex* q = p->right;
                p->bal = 0;
                q->bal = 0;
                p->right = q->left;
                q->left = p;
                p = q;
                VR = 1;
                HR = 0;
            }
            else HR = 0;
        }
    }
}

void TreeSearch(Vertex* p, char* data, int sym_count) {

    if (p != NULL)
    {
        if (strncmp(p->data->Birthday, data, sym_count) == 0) {
            cout << p->data->Name << "\t\t" << p->data->Department << "\t\t\t" << p->data->Post << "\t\t" << p->data->Birthday << endl;
            TreeSearch(p->next, data, sym_count);
        }
        else if (strncmp(p->data->Birthday, data, sym_count) > 0) {
            TreeSearch(p->left, data, sym_count);
        }
        else if (strncmp(p->data->Birthday, data, sym_count) < 0) {
            TreeSearch(p->right, data, sym_count);
        }
    }
}

void TreePrint(Vertex* x) {
    if (x) {
        TreePrint(x->left);
        cout << x->data->Name << "\t\t" << x->data->Department << "\t\t\t" << x->data->Post << "\t\t" << x->data->Birthday << endl;
        TreePrint(x->next);
        TreePrint(x->right);
    }
}

void Delete_Tree(Vertex*& p) {
    if (p != NULL) {
        Delete_Tree(p->left);
        Delete_Tree(p->right);
        delete p;
    }
}

void Tree(Record* arr[], int n) {
    Vertex* root = NULL;
    cout << "Name                             Department                      Post                           Birth date\n" << endl;
    for (int i = 0; i < n; i++) {
        auto x = arr[i];
        DBD(x, root);
    }
    TreePrint(root);
    cout << endl;
    printf("+-----------------------------+\n");
    cout << endl << "Enter full birthday: ";
    char temp_birth[10];
    cin >> temp_birth;
    sym_count = strlen(temp_birth);
    if (sym_count == 8) {
        system("CLS");
        cout << "Name                             Department                      Post                           Birth date\n" << endl;
        TreeSearch(root, temp_birth, sym_count);
        system("pause");
        Delete_Tree(root);
    }else{
        cout << "The date was entered incorrectly";
        Delete_Tree(root);
    }
}

void Gilbert_Moore(const int n, double p[], int Length[], char c[][20]) {
    double* q = new double[n];
    Length[0] = ceil(log2(1 / p[0]));
    q[0] = p[0] / 2;

    for (int i = 1; i < n; ++i) {
        double tmp = 0;
        for (int k = 0; k < i; k++)
            tmp += p[k];

        q[i] = tmp + p[i] / 2;
        Length[i] = ceil(log2(1 / p[i]));  
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < Length[i]; ++j) {
            q[i] *= 2;
            c[i][j] = floor(q[i]) + '0';
            if (q[i] >= 1) {
                q[i] -= 1;
            }
        }
    }
}

unordered_map<char, int> get_char_counts_from_file(const string& file_name, int& file_size)
{
    ifstream file(file_name, ios::binary);
    if (!file.is_open())
    {
        throw runtime_error("Could not open file");
    }
    char ch_arr[sizeof(Record) * N];
    file.read((char*)ch_arr, sizeof(Record) * N);
    file.close();

    unordered_map<char, int> counter_map;
    file_size = 0;
    for (auto ch : ch_arr)
    {
        counter_map[ch]++;
        file_size++;
    }
    return counter_map;
}

vector<pair<double, char>> calc_probabilities(const unordered_map<char, int>& counter_map, int count)
{
    vector<pair<double, char>> probabilities;
    probabilities.reserve(counter_map.size());
    for (auto i : counter_map)
    {
        probabilities.emplace_back(make_pair((double)i.second / count, i.first));
    }
    return probabilities;
}

void coding()
{
    int file_size;
    unordered_map<char, int> counter_map;
    counter_map = get_char_counts_from_file("testBase2.dat", file_size);

    auto probabilities = calc_probabilities(counter_map, file_size);
    counter_map.clear();

    sort(probabilities.begin(), probabilities.end(), greater<>());
    cout << "Probabil.  char\n";
    for (auto i : probabilities)
    {
        cout << fixed << i.first << " | " << i.second << '\n';
    }

    const int n = (int)probabilities.size();

    auto c = new char[n][20];
    auto Length = new int[n];
    auto p = new double[n];
    for (int i = 0; i < n; ++i)
    {
        p[i] = probabilities[i].first;
    }

    double shen = 0;
    Gilbert_Moore(n, p, Length, c);
    cout << "\nMur Code:\n";
    cout << "\nCh  Prob      Code\n";
    double avg_len = 0;
    double entropy = 0;
    for (int i = 0; i < n; i++)
    {
        avg_len += Length[i] * p[i];
        entropy -= p[i] * log2(p[i]);
        printf("%c | %.5lf | ", probabilities[i].second, p[i]);
        for (int j = 0; j < Length[i]; ++j)
        {
            printf("%c", c[i][j]);
        }
        cout << '\n';
        shen += p[i];
    }
    cout << "Average length = " << avg_len << '\n'
        << "Entropy = " << entropy << '\n'
        << "Average length < entropy + 2\n"
        << "N = " << n << endl;
}

void Menu(Record* unsorted_ind_array[], Record* sorted_ind_array[])
{
    int search_ind, search_n = -1;
    while (true)
    {
        string chose = Output("1: Show unsorted list\n"
            "2: Show sorted list\n"
            "3: Search\n"
            "4: Tree\n"
            "5: Coding\n"
            "Any key: Exit");
        switch (chose[0])
        {
        case '1':
            Menu_list(unsorted_ind_array);
            break;
        case '2':
            Menu_list(sorted_ind_array);
            break;
        case '3':
            Search(sorted_ind_array, search_ind, search_n);
            break;
        case '4':
            if (search_n == -1)
            {
                cout << "Please search anything before making tree\n";
            }
            else
            {
                Tree(&sorted_ind_array[search_ind], search_n);
            }
            break;
        case '5':
            coding();
            break;
        default:
            return;
        }
    }
}

int main()
{
    Ochered* head = Load_base();
    if (!head)
    {
        cout << "File not found" << endl;
        return 1;
    }
    auto unsorted_ind_arr = new Record * [N];
    auto sorted_ind_arr = new Record * [N];
    Index_array(unsorted_ind_arr, head);
    Digital_Sort(head);
    Index_array(sorted_ind_arr, head);
    Menu(unsorted_ind_arr, sorted_ind_arr);
} 
