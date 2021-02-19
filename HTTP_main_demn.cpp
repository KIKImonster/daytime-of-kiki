#include"db.hpp"
#include"httplib.h"

using namespace httplib;
blog_system::TableBlog* table_blog;
blog_system::TableTag* table_tag;
//业务处理模块，这里处理函数内部是需要对数据库进行操作的，因此我们有必要在之前创建好数据库的操作句柄
void InsertBlog(Request& req, Response& r)
{
	return;
}
void DeleteBlog(Request& req, Response& r)
{
	return;
}
void UpdatBlog(Request& req, Response& r)
{
	return;
}
void GetAllBlog(Request& req, Response& r)
{
	return;
}
void GetOneBlog(Request& req, Response& r)
{
	return;
}
void InsertTag(Request& req, Response& r)
{
	return;
}
void DeleteTag(Request& req, Response& r)
{
	return;
}
void UpdateTag(Request& req, Response& r)
{
	return;
}
void GetAllTag(Request& req, Response& r)
{
	return;
}
void GetOneTag(Request& req, Response& r)
{
	return;
}


int main()
{
	MYSQL* mysql = blog_system::MysqlInit();
	table_blog = new blog_system::TableBlog(mysql);
	table_tag = new blog_system::TableTag(mysql);
	Server server;//实例化一个Server对象，----map表（请求，处理函数的指针）
	server.set_base_dir("./www");//设置相对根目录
	//博客的增删改查
	server.Post("/blog", InsterBlog);
	//server.Delete("/blog//\d+", DeleteBlog)
	server.Delete(R"(/blog/(\d+)", DeleteBlog);//正则表达式，取出一个整形数据R(）代表去除（）内的转义，正则的（）代表取出数据；
	server.put(R"(/blog/(\d+)", UpdateBlog);

	server.Get("/blog", GetAllBlog);
	server.Get(R"(/blog/(\d+)",GetOneBlog);
	//tag的增删改查
	server.Post("/tag", InsertTag);
	server.Delete(R"(/tag/(\d+)", DeleteTag);
	server.Put(R"(/tag/(\d+)", UpdateTag);
	server.Get("/tag", GetAllTag);//获取所有博客
	server.Get(R"(/tag/(\d+)", GetOneTag);//获取一个博客

	sever.listen("0,0,0,0", 9000);

	return 0;
}


