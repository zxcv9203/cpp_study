# 문자열 클래스 만들어보기

문자열 클래스는 다음과 같은 내용을 지원해야 합니다.

1. 문자 (char )로 부터 문자열 생성, C 문자열 (char *)로 부터의 생성

2. 문자열 길이를 구하는 함수

3. 문자열 뒤에 다른 문자열 붙이기

4. 문자열 내에 포함되어 있는 문자열 구하기

5. 문자열이 같은지 비교

6. 문자열 크기 비교(사전순)

기존 C언어에서는 문자열을 나타내기 위해 널 종료 문자열(Null-terstd::minating string)이라는 개념을 도입해서 문자열 끝에 NULL 문자를 붙여 문자열을 나타내는 방식을 사용하였습니다.

하지만 C 언어 문자열을 사용하는데에는 번거로움이 많았는데, 예를 들어서 만들어진 문자열의 크기를 바꾼다던지, 문자열 뒤에 다른 문자열을 붙인다던지 등의 작업은 상당히 프로그래머 입장에서는 귀찮을 수 밖에 없습니다.

이와 같은 작업들을 문자열 클래스를 따로 만들어서 클래스 차원에서 지원해주면 상당히 편할텐데 말이지요

그래서 우리는 직접 문자열 클래스를 만들고자 합니다.

사실 C++에서는 표준 라이브러리로 string 클래스를 지원하고 있습니다.

```
C++에서는 정말 왠만하면 char 배열을 사용하는 것 보다 string을 사용하여 문자열을 다루는 것을 권장합니다.
```

하지만 string 클래스를 사용하기 이전에 우리는 직접 MyString 이라는 우리 만의 문자열 클래스를 만들고자 합니다.

일단 간단히 생각해서 우리가 만들 MyString 클래스의 멤버 변수로 무엇이 필요할지 생각해봅시다.

아마 대표적으로 두 개의 데이터들이 필요하다고 볼 수 있습니다.

1. 문자열 데이터가 저장된 공간을 가리키는 포인터

2. 문자열 데이터의 길이

왜 객체에 문자열 데이터를 직접 보관하는 것이 아니라 그 저장된 공간을 가리키는 포인터를 보관하냐고 물을 수 있습니다.

이렇게 하는 이유는 나중에 문자열 데이터의 크기가 바뀔 때, 저장된 공간을 가리키는 방식으로 하면 그 메모리를 해제한 뒤에, 다시 할당할 수 있지만 직접 보관하면 그럴 수 없기 때문입니다.

또한, 문자열 데이터의 길이를 보관하는 이유는 문자열 길이를 사용할 일이 굉장히 많은데, 그 때마다 계속 길이를 구하는 것은 상당히 불필요한 일이기 때문입니다.

따라서 길이를 한 번 구해 놓고 길이가 바뀔 때까지 변경하지 않는 방법이 유용할 것입니다.

```cpp
class MyString {
	private:
		char *string_content; // 문자열 데이터를 가리키는 포인터
		int string_length; // 문자열 길이
};
```

일단 위 두 정보는 private로 설정하였습니다.

왜냐하면 우리는 다른 프로그래머가 저의 MyString을 이용하면서 위와 같은 중요한 정보들에 함부로 접근하기를 원치 않기때문입니다.

프로그래머가 실수로 string_length를 조작하는 명령을 썼다가 자칫 잘못해서 이상한 값이 들어가면 많은 문제가 발생할 수 있습니다.

그렇기에 우리는 다른 프로그래머가 저의 MyString을 string_length나 string_content를 직접 만지지 않더라도 원하는 작업들을 충분히 수행할 수 있게 함수를 제공해야 할 것입니다.

그럼 생성자는 어떻게 만들어야 할까요?

일단 구현하고 싶은 내용을 충족시키기 위해서는 아래와 같은 생성자들을 만들어야 합니다.

```cpp
MyString(char c);
MyString(const char *str);
MyString(const MyString &str);
```

위와 같은 생성자들을 만들기 전에 어떠한 방식으로 문자열을 저장할 것인지에 대해 먼저 생각해보도록 합시다.

과연 그대로 string_content에 C 형식의 문자열 (널 종료 문자열)을 보관하는 것이 좋을까요, 아니면 필요없는 정보들을 빼고 (즉 맨 마지막의 널 문자) 실제 '문자'만 해당하는 부분만을 넣을까요

C 형식의 문자열을 그대로 보관한다면, 문자열의 끝 부분을 쉽게 체크할 수 있다는 장점이 있지만 이 문제는 우리가 string_length라는 변수를 같이 도입함으로써 해결할 수 있게 되었습니다.

따라서, 저희 MyString 클래스에서는 실제 문자에만 해당하는 내용만을 string_content에 보관하도록 하겠습니다.

```cpp

```