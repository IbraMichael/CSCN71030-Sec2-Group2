#include "pch.h"
#include "CppUnitTest.h"

extern "C" typedef enum role {
	DOCTOR_ROLE,
	NURSE_ROLE
} ROLE;

extern "C" typedef struct Enode {
	char username[100];
	char password[100];
	char name[100];
	ROLE r;
	struct Enode* next;
}ENODE;
extern "C" ENODE * createNode(char* username, char* password, char* name, int role);

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char name[100] = "Bob";
			char password[100] = "password";
			ENODE* e = createNode(name, password, name, DOCTOR_ROLE);
			Assert::IsTrue(name == e->name);
			Assert::IsTrue(name == e->username);
			Assert::IsTrue(password == e->password);
			Assert::AreEqual(DOCTOR_ROLE, e->r);
			free(e);
		}
	};
}
