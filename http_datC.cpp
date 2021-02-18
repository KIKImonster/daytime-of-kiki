
#include<iostream>
#include<mysql/mysql.h>
#include<jsoncpp/json/json.h>
#inlcude<mutex>

#define MYSQL_HOST "127.0.0.1"
#define MYSQL_USER "root"
#define MYSQL_PSWD " 818817Ma.."
#define MYSQL_DB "db_blog"

namespace blog_system{
	static std::mutex g_mutex;
	MYSQL* MysqlInit()
	{
		MYSQL* mysql;
		mysql = mysql_init(NULL);
		if (mysql == NULL)
		{
			printf("init mysql erron:\n");
			return NULL;
		}
		//连接服务器
		if (mysql_real_connect(mysql, MYSQL_HOST, MYSQL_UESR, MYSQL_PSWD, NULL, 0, NULL, 0) == NULL)
		{
			printf("connect mysql erron:%s\n",mysql_erron(mysql));
			mysql_close(mysql);
			return NULL;
		}
		//设置字符集
		if (mysql_set_character(mysql, "utf8") != 0)
		{
			printf("set_character mysql erron:%s\n", mysql_erron(mysql));
			mysql_close(mysql);
			return NULL;
		}
		//选择数据库
		if (mysql_select_db(mysql, MYSQL_DB) != 0)
		{
			printf("select db erron:%s\n", mysql_erron(mysql));
			mysql_close(mysql);
			return NULL;
		}
		return mysql;
	}//向外提供接口返回初识化完成的mysql句柄(连接服务器，选择数据库，设置字符集）
	void MysqlRelease(MYSQL* mysql)
	{
		if (mysql)
		{
			mysql_close(mysql);
		}
		return;
	}//销毁句柄
	bool MysqlQuery(MYSQL* mysql, char* sql)
	{
		//执行数据库操作语句的共有接口
		int ret = mysql_query(mysql, sql);
		if (ret != 0)
		{
			printf("query sql:[%s] failed:%s\n", sql, mysql_erron(mysql);
		}
	}

	class TableBlog
	{
	public:
		TableBlog(MYSQL* mysql)
			:_mysql(mysql)
		{}
		//blog中取出博客信息，组织sql语句，将数据插入数据库
		//id ，tag_id ,title ， content ，c_time
		bool Insert(Json::Value& blog)
		{

#define INSERT_BLOG "insert tb_blog values(null，'%d', '%s', '%s',now());"
			/*int len = blog["content"].asString().size() + 4096;
			std::string sql;
			sql.resize(len);*/
			int len = blog["content"].asString().size() + 4096;
			char* tmp = (char*)malloc(len);
			
			sprintf(tmp, INSERT_BLOG,
	            blog["tag_id"].asInt(),
				blog["title"].asCString(),
				blog["content"].asCString()
				);
			bool ret = MysqlQuery(_mysql, tmp);
			free(tmp);
			return ret;
		}

		bool Delete(int blog_id)
		{
#define DELETE_BLOG "delete from tb_blog where id = %d;"
			char* tmp[4096] = { 0 };
			sprintf(tmp, DELETE_BLOG, blog_id);
			bool ret = Mysql_query(_mysql, tmp);
			return ret;
		}
		bool Update(Json::Value& blog)
		{
#define UPDATE_BLOG "update tb_blog set tltle = '%s', content = '%s', tag_id = '%d';"
			int len = blog["content"].asString().size() + 4096;
			char* tmp = (char*)malloc(len);

			sprintf(tmp, UPDATE_BLOG,
				blog["title"].asCString(),
				blog["content"].asCString(),
				blog["tag_id"].asInt()
				);
			bool ret = Mysql_query(_mysql, tmp);
			free(tmp);
			return ret;
		}
		bool GetALL(Json::Value* blogs)
		{
			//执行查询语句，保存结果集，遍历结果集
#define GETALL_BLOG "select id,tag_id,title,c_time from tb_blog;"
			g_mutex.lock();
			bool ret = MysqlQuery(_mysql,const GETALL_BLOG);
			if (ret == false)
			{
				printf("story all blogs result failed:&s\n", mysql_erron(_mysql));
				g_mutex.unlock();
				return false;
			}
			MYSQL_RES* res = mysql_store_result(_mysql);
			g_mutex.unloc();
			if (res == NULL)
			{
				printf("store all blog result failed:%s\n", mysql_erron(_mysql));
				return false;
			}
			//遍历结果集
			int row_num = mysql_num_rows(res);
			for (int i = 0; i < row_num; i++)
			{
				MYSQL_ROW row = mysql_fetch_row(res);
				Json::Value blog;
				blog["id"] = std::stoi(row[0]);
				blog["title"] = std::stoi(row[2]);
				blog["tag_id"] = std::stoi(row[1]);
				blog["c_time"] = std::stoi(row[3]);
				blogs->append(blog);//添加Json数组元素
			}
			mysql_free_result(res);
			return true;
		
		}
		bool GetOne(Json::Value* blog)
		{
#define GETONE_BLOG "select tag_id,title, content,c_time from tb_blog where id = %d;"
			char tmp[1024] = { 0 };
			sprintf(tmp, GETONE_BLOG, (*blog)["id"].asInt());
			g_mutex.lock();
			bool ret = MysqlQuery(_mysql, tmp);
			if (ret == false)
			{
				g_mutex.unlock();
				return false;
			}
			MYSQL_RES* res = mysql_store_result(_mysql);
			g_mutex.lock();
			if (res == NULL)
			{
				printf("store all_one blog result failed:%s\n", mysql_erron(_mysql));
				return false;
			}
			int row_num = mysql_num_rows(res);
			if (row_num != 1)
			{
				printf("get one blog reuslt erron\n");
				mysql_free_result(res);
				return false;
			}
			MYSQL_ROW row = mysql_fetch_row(res);
			(*blog)["tag_id"] = std::stoi(row[0]);
			(*blog)["title"] = std::stoi(row[1]);
			(*blog)["content"] = std::stoi(row[2]);
			(*blog)["c_time"] = std::stoi(row[3]);

			mysql_free_result(res);
			return true;
		}

	private:
		MYSQL* _mysql;
	};
	class TableTag
	{

	public:
		TableTag(MYSQL* mysql)
			:_mysql(mysql)
		{}
		bool Insert(Json::Value& tag)
		{

#define INSERT_TAG "insert tb_blog values(null, '%s');"
			char tmp[1024] = { 0 };
			sprintf(tmp, INSERT_TAG,tag["tag_name"].asCString());
			bool ret = MysqlQuery(_mysql, tmp);
			return ret;
		}
		bool Delete(int id)
		{
#define DELETE_TAG "delete from tb_tag where tag_id = %d;"
			char tmp[1024] = { 0 };
			sprintf(tmp, DELETE_TAG, id);
			return MysqlQuery(_mysql, tmp);
		}
		bool Update(Json::Value& tag)
		{
#define UPDATE_TAG "update tb_tag set tag_name = '%s' where tag_id = %d;"
			char tmp[1024] = { 0 };
			sprintf(tmp, UPDATE_TAG, tag["tag_name"].asCString(),tag["tag_id"].asInt());
			return MysqlQuery(_mysql, tmp);
		}
		bool GetALL(Json::Value* tags)
		{
#define GETALL_TAG " select tag_id,tag_name from tb_table;"
			g_mutex.lock();
			bool ret = MysqlQuery(_mysql, GETALL_TAG);
			if (ret == false)
			{
				g_mutex.unlock();
				return false;
			}
			MYSQL_RES* res = mysql_store_result(_mysql);
			g_mutex.unlock();
			if (res == NULL)
			{
				printf("store all tag result failed:%s," mysql_error(_mysql));
				return false;
			}
			int row_num = mysql_num_rows(res);
			for (int i = 0; i < row_num, i++)
			{
				MYSQL_ROW row = mysql_fetch_row(res);
				Json::Value tag;
				tag["tag_id"] = std::stoi(row[0]);
				tag["tag_name"] = std::stoi(row[1]);
				tag->appeng(tag);
			}
			mysql_free_result(tag);
			return true;
		}
		bool GetOne(Json::Value* tag)
		{
#define GETONE_TAG "select tag_name from tb_tag where tag_id = %d;"
			char tmp[1024] = { 0 };
			sprintf(tmp, GETONE_TAG, (*tag)["tag_id"].asInt());
			g_mutex.lock();
			bool ret MysqlQuery(_mysql, tmp);
			if (ret == false)
			{
				g_mutex.unlock();
				return false;
			}
			MYSQL_RES* res = mysql_store_result(_mysql);
			g_mutex.unlock();
			if (res == NULL)
			{
				printf("store tag one result failed:%s", mysql_error(_mysql));
				return false;
			}
			int row_num = mysql_num_rows(res);
			if (row_num != 1)
			{
				printf("get one tag reslut erron\n");
				mysql_free_result(res);
				return false;
			}
			MYSQL_ROW row = mysql_fetch_row(res);
			(*tag)["name"] = row[0];
			mysql_free_result(res);
			return true;
		}

	private: 
		MYSQL* _mysql;

	};
}









:wq

