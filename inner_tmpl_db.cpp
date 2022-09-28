/*����һ��ģ���ڴ����ݿ⣬Ϊ�˼����ڴ�ĸ��ƣ��ӿ����ݶ�ȡ�����*/

#include "tmpl_db.h"

int Tmpl_db::get_size()
{
	return m_name_vector.size();
}


void Tmpl_db::delete_tmpl(int arg_i)
{
	auto i = static_cast<size_t>(arg_i);
	if (i >= m_capacity || i < 0) {
		return;
	}
	else if (i == m_capacity - 1L) {//ɾ�����һ��tmpl
		memset(m_data +(m_capacity - 1L) * m_tmpl_size, 0, m_tmpl_size);
		m_name_vector.erase(std::begin(m_name_vector) += i);
	}
	else {//ɾ��һ��tmpl��Ȼ�󽫺��沿��Ԫ��ǰ��һ��ɾ�����һ��tmpl
		memcpy_s(m_data + i * m_tmpl_size,
			(m_capacity - (i + 1)) * (m_tmpl_size),
			m_data + (i + 1) * m_tmpl_size,
			(m_capacity - (i + 1)) * m_tmpl_size);
		memset(m_data + (m_capacity - 1L) * m_tmpl_size, 0, m_tmpl_size);
		m_name_vector.erase(std::begin(m_name_vector) += i);
	}
}

void Tmpl_db::clear()
{
    memset(m_data,0,(m_capacity - 1L) * m_tmpl_size);
	m_name_vector.clear();
}


std::string Tmpl_db::get_name(int num)
{
	return m_name_vector.at(num);
}


void Tmpl_db::add(unsigned char* new_data, std::string s = "undefined name") {
	
	bool update_flag = false;
	for (size_t i = 0; i < m_name_vector.size(); i++) {
		if (m_name_vector[i] == s) {
			update_flag = true;
			this->update(new_data, i);
			return;
		}
	}

	if (!update_flag) {
		if (m_name_vector.size() < m_capacity) {
			memcpy_s(m_data + static_cast<long long>(m_name_vector.size()) * m_tmpl_size, m_tmpl_size, new_data, m_tmpl_size);
			m_name_vector.push_back(s);
		}
		else if (m_name_vector.size() >= m_capacity) {
			resize();
			add(new_data, s);
		}
	}
}


void Tmpl_db::update(unsigned char* arg_update_data, int arg_matched_index)
{
	int size = this->get_size();
	if (0 <= arg_matched_index &&  arg_matched_index < size) {
		errno_t e = memcpy_s(m_data + m_tmpl_size * arg_matched_index, m_tmpl_size, arg_update_data, m_tmpl_size);
	}
	else {
		throw "index is out of scope";
	}
}


void Tmpl_db::resize() {
	if (m_capacity == 0)
	{
		m_data = new unsigned char[m_tmpl_size * 1]{};
		m_capacity = 1;
	}
	else {//�����ڴ棬ԭ�ڴ渴�Ƶ����ڴ�
		unsigned char* new_data = new unsigned char[m_tmpl_size * m_capacity * 2L]{};
		memset(new_data, 0, m_tmpl_size * m_capacity * 2L);
		memcpy_s(new_data, m_tmpl_size * static_cast<long long>(m_name_vector.size()), m_data, m_tmpl_size * static_cast<long long>(m_name_vector.size()));
		delete m_data;
		m_data = new_data;
		m_capacity *= 2;
	}
}



