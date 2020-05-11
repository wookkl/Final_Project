# Final_Project


#활동사항
- 2020-05-01
```
[수행일지]
   안드로이드 --> 아두이노 송신단 제거 
```
- 2020-05-02
```
[수행일지]
   - 블루투스 연결 및 페어링 버튼생성
   - 라이브러리 2개 Merge
```

- 2020-05-03
```
[수행일지]
   - 버튼확인 및 센서값들 split한후 App상에 표시
```
- 2020-05-04
```
[수행일지]
   - 버튼오류로 인한 Rollback 
   -  ahrs 센서값 6축 아두이노 --> 안드로이드 스튜디오 Data전송.
```
- 2020-05-05
```
[수행일지]
   - Ebimu 및 Flex 센서값 송신을 위한 아두이노 코드작성

[필요연구]
   - 안드로이드 스튜디오와 동기식 데이타전송 필요, 안드로이드 스튜디오상 Lifecycle 변경 필요.
```
- 2020-05-06
```
[수행일지]
   - Ebimu 및 Flex 센서값 동기식 전송 완료, 앱 실행시 자동연결 완성, LifeCycle 구상완료.

[필요연구]
   - LifeCycle 맞춰서 코딩 및 브로드캐스팅 연구필요.
```
- 2020-05-07
```
[수행일지]
   - 데이터 수신 스레드 문제해결 (split함수 오류 -> charAt 사용해 문자열 재생성)
   - 액티비티 생명주기 문제해결 (back키 누를 시 강제종료 -> onDestroy 함수를 생성해 소켓, 스레드, in/out stream을 close)

[필요연구]
   - 브로드캐스팅을 통해 블루투스 connect/disconnect 를 판단하고 해당하는 루틴 생성
   - 멀티페어링 (소켓, 스레드) 생성구상
```

- 2020-05-08
```
[수행일지]
   - 브로드캐스트 학습 완료 및 reconnectButton 구상 완료.
[필요연구]
   - 브로드캐스트 적용
```

- 2020-05-09
```
[수행일지]
   - Jarduino HC-05 Baudrate 확인 및 브로드캐스트 리시버 학습
[필요연구]
   - 탑 다운 방식으로 멀티페어링부터 재구성 필요, Data 수신 뒤 동기화 학습 필요
```

- 2020-05-10
```
[수행일지]
   - 기존 한손으로만 하는 방식 포기 -> 동기화 위해 두 손을 동시에 하는 더블포인트 Research
[필요연구]
   - 재료 구비 필요
```

- 2020-05-11
```
[수행일지]
   - 블루투스 멀티포인트 성공, 2개의 아두이노로부터 Data받아옴.
   - 추가 라이브러리 사용. (수신측 1개의 스레드로 post한 후 main에서 왼손 오른손 나뉨)
[필요연구]
   - 소켓, 스레드를 닫는 생명주기 재 설정 필요(onDestroy)
   - 브로드캐스트 리시버로 양측 아두이노 상태 확인 필요
   - 양측이 모두 연결됐을때만 Data를 받을 수 있게 해야 동기화 가능.
   - 동기화 방법 연구 필요.
```