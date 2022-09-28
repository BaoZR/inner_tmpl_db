/*这是一个模板内存数据库，为了减少内存的复制，加快数据读取而设计*/

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
	else if (i == m_capacity - 1L) {//删除最后一个tmpl
		memset(m_data +(m_capacity - 1L) * m_tmpl_size, 0, m_tmpl_size);
		m_name_vector.erase(std::begin(m_name_vector) += i);
	}
	else {//删除一个tmpl，然后将后面部分元素前移一格，删除最后一个tmpl
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
	memset(m_data,0, m_capacity * m_tmpl_size);
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
	else {//扩大内存，原内存复制到新内存
		unsigned char* new_data = new unsigned char[m_tmpl_size * m_capacity * 2L]{};
		memset(new_data, 0, m_tmpl_size * m_capacity * 2L);
		memcpy_s(new_data, m_tmpl_size * static_cast<long long>(m_name_vector.size()), m_data, m_tmpl_size * static_cast<long long>(m_name_vector.size()));
		delete m_data;
		m_data = new_data;
		m_capacity *= 2;
	}
}



