#pragma once
#ifndef __TMPL_DB__
#define __TMPL_DB__

/*����һ��ģ���ڴ����ݿ⣬Ϊ�˼����ڴ�ĸ��ƣ��ӿ����ݶ�ȡ�����*/

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
	//��ȡģ�����
	int get_size();
	void delete_tmpl(int);
	//���ģ���ģ����
	void clear();
	std::string get_name(int);//��ȡ��Ӧ������
	//��ӻ��滻
	void add(unsigned char*, std::string);
	//��֤�����ģ��ʹ�ã���Ҫ����ȶԳɹ���index��index��0��ʼ
	void update(unsigned char*, int index);
	void resize();
private:
	std::vector<std::string> m_name_vector;//���ڱ����û���//�����Եõ�ģ������
	//int m_size;//ģ�����
	size_t m_tmpl_size;//�ڲ�����ģ���С
	size_t m_capacity;//����
	unsigned char* m_data;
};

#endif // __TMPL_DB_

