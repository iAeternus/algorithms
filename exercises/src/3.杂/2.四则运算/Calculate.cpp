/**
 * @brief 正浮点数构成的非全括号式 四则运算
 * @author Ricky
 * @date 2023/12/28
 * @version 1.0
 */
#include <iostream>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <string>
#include <stack>

class CalUtils
{
public:
    CalUtils() = delete;
    CalUtils(const CalUtils &other) = delete;
    CalUtils &operator=(const CalUtils &other) = delete;
    CalUtils(CalUtils &&other) noexcept = delete;
    CalUtils &operator=(CalUtils &&other) noexcept = delete;

    // 四则运算处理函数
    inline static double calculate(const std::vector<std::string> &formula)
    {
        std::stack<double> vals;     // 操作数栈
        std::stack<std::string> ops; // 运算符栈

        for (const auto &s : formula)
        {
            if (s == "(") // 左括号，压入运算符栈
            {
                ops.push(s);
            }
            else if (isOps(s))
            {
                // 如果当前运算符优先级小于等于栈顶符号优先级，则对操作数栈进行计算
                while (!ops.empty() && ops.top() != "(" && opPri.at(s) <= opPri.at(ops.top()))
                {
                    eval(vals, ops);
                }
                ops.push(s);
            }
            else if (s == ")")
            {
                // 计算完一对括号的表达式
                while (ops.top() != "(")
                {
                    eval(vals, ops);
                }
                ops.pop();
            }
            else // 数字，压入操作数栈
            {
                vals.push(std::stod(s));
            }
        }

        // 因为没有右括号，所以运算符栈不空，继续计算
        while (!ops.empty())
        {
            eval(vals, ops);
        }

        return vals.top();
    }

    // 这个更通用，接收字符串作为输入
    inline static double calculate(const std::string &formula)
    {
        return calculate(toStringVector(formula));
    }

    // 从文件中读读取若干算式
    inline static std::vector<std::vector<std::string>> getFormulas(const std::string &filePath)
    {
        std::ifstream file(filePath);

        std::string line;
        std::vector<std::vector<std::string>> result;

        try
        {
            while (std::getline(file, line))
            {
                result.push_back(toStringVector(line));
            }
            file.close();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        return result;
    }

    // 从文件中读取一行算式
    inline static std::vector<std::string> getFormula(const std::string &filePath)
    {
        std::ifstream file(filePath);

        std::string line;
        std::vector<std::string> result;

        try
        {
            std::getline(file, line);
            result = toStringVector(line);
            file.close();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        return result;
    }

    // 将算式转换为字符串
    inline static std::string formulaToString(std::vector<std::string> formula)
    {
        std::string result;
        for (const auto &s : formula)
        {
            result.append(s);
        }
        return result;
    }

private:
    // 运算优先级
    inline static const std::unordered_map<std::string, int> opPri = {
        {"+", 1},
        {"-", 1},
        {"*", 2},
        {"/", 2},
    };

    template <class T>
    inline static T getTop(std::stack<T> &stack)
    {
        T val = stack.top();
        stack.pop();
        return val;
    }

    inline static bool isOps(const std::string &op)
    {
        return op == "+" || op == "-" || op == "*" || op == "/";
    }

    inline static bool isOps(char op)
    {
        return op == '+' || op == '-' || op == '*' || op == '/';
    }

    // 计算函数
    inline static void eval(std::stack<double> &vals, std::stack<std::string> &ops)
    {
        if (vals.size() < 2)
            return;

        std::string op = getTop<std::string>(ops);
        double v = getTop<double>(vals);

        if (op == "+")
            v = getTop<double>(vals) + v;
        else if (op == "-")
            v = getTop<double>(vals) - v;
        else if (op == "*")
            v = getTop<double>(vals) * v;
        else if (op == "/")
        {
            try
            {
                v = getTop<double>(vals) / v;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        vals.push(v);
    }

    inline static bool isNumber(char ch)
    {
        return ch >= '0' && ch <= '9';
    }

    // 从算式的指定开始位置获取浮点数
    inline static std::string getDoubleFromString(const std::string &formula, int i, int &nextIndex)
    {
        if (i < 0 || i >= formula.size())
            return "";

        std::string str;
        while (isNumber(formula[i]) || formula[i] == '.')
        {
            str += formula[i];
            ++i;
        }
        nextIndex = i - 1; // 下一个item开始的索引
        return str;
    }

    inline static bool isBracket(char ch)
    {
        return ch == '(' || ch == ')';
    }

    // 将算式字符串转化为字符串数组
    inline static std::vector<std::string> toStringVector(const std::string &formula)
    {
        std::string item;
        std::vector<std::string> result;
        for (int i = 0; i < formula.size(); ++i)
        {
            char ch = formula[i];
            if (isNumber(ch))
            {
                // 获取浮点数并将 i 指向下一个 item 的位置
                item = getDoubleFromString(formula, i, i);
            }
            else if (isOps(ch) || isBracket(ch))
            {
                item += ch;
            }
            result.push_back(item);
            item = "";
        }
        return result;
    }
};

int main()
{
    std::vector<std::string> f1 = {"1", "*", "4", "+", "5"};                                                   // 9
    std::vector<std::string> f2 = {"1", "+", "2", "-", "3", "*", "(", "4", "-", "5", "+", "6", ")", "-", "7"}; // -19

    std::cout << CalUtils::formulaToString(f1) << " = " << CalUtils::calculate(f1) << std::endl;
    std::cout << CalUtils::formulaToString(f2) << " = " << CalUtils::calculate(f2) << std::endl;

    std::cout << "============================================\n";

    // 以下这种最实用

    std::string f3 = "1*4+5";                                                                    // 9
    std::string f4 = "1+2-3*(4-5+6)-7";                                                          // -19
    std::string f5 = "((1+1024)*36.75-18.375)/(22.125+15.1*(12.9-1))-(1234.456*0.375)*4.5+1024"; // -872.586

    std::cout << f3 << " = " << CalUtils::calculate(f3) << std::endl;
    std::cout << f4 << " = " << CalUtils::calculate(f4) << std::endl;
    std::cout << f5 << " = " << CalUtils::calculate(f5) << std::endl;

    std::cout << "============================================\n";

    std::vector<std::vector<std::string>> formulas = CalUtils::getFormulas("formulas.txt");
    for (const auto &formula : formulas)
    {
        std::cout << CalUtils::formulaToString(formula) << " = " << CalUtils::calculate(formula) << std::endl;
    }

    return 0;
}