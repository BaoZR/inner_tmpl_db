#pragma once
#ifndef __TMPL_DB__
#define __TMPL_DB__

/*这是一个模板内存数据库，为了减少内存的复制，加快数据读取而设计*/

#include <string>
#include <vector>

constexpr int REG_TIMES = 6;
constexpr int TMPL_SIZE = 2048 * REG_TIMES;

class Tmpl_db 
{
public:
	explicit Tmpl_db(int tmpl_size = TMPL_SIZE)  {
		m_data = nullptr;
		m_name_vector = std::vector<std::string>();
		m_capacity = 0;
		m_tmpl_size = tmpl_size;
	}
	~Tmpl_db() {
		delete m_data;
	}
	unsigned char* get() { return m_data; }
	//获取模板个数
	int get_size();
	void delete_tmpl(int);
	//清空模板和模板名
	void clear();
	std::string get_name(int);//获取对应的名字
	//添加或替换
	void add(unsigned char*, std::string);
	//验证后更新模板使用，需要传入比对成功的index，index从0开始
	void update(unsigned char*, int index);
	void resize();
private:
	std::vector<std::string> m_name_vector;//用于保存用户名//还可以得到模板数量
	//int m_size;//模板个数
	size_t m_tmpl_size;//内部单个模板大小
	size_t m_capacity;//容量
	unsigned char* m_data;
};

#endif // __TMPL_DB_

