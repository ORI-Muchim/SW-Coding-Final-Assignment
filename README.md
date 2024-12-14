# Stock Market Simulator

주식 시장 시뮬레이션 프로그램입니다. 실제 주식 거래와 유사한 환경에서 모의 투자를 체험할 수 있습니다.

## Prerequisites

프로그램 실행을 위해 다음이 필요합니다:

- GCC 컴파일러
- C 표준 라이브러리
- Unix 기반 시스템 (Linux/MacOS) 또는 Windows

## Installation

1. 저장소 클론:
```bash
git clone [repository-url]
cd stock-simulator
```

2. 프로그램 컴파일:
```bash
gcc -I. -o stock_simulator main.c user_system.c stock_system.c portfolio_system.c
```

3. 초기 데이터 설정:
```bash
# trading_data 디렉토리 생성
mkdir -p trading_data

# stocks.txt 파일 생성 및 초기 데이터 입력
cat > trading_data/stocks.txt << EOL
005930 삼성전자 전자 72000 0.0
035420 NAVER IT 220000 0.0
000660 SK하이닉스 반도체 130000 0.0
005380 현대차 자동차 185000 0.0
051910 LG화학 화학 580000 0.0
035720 카카오 IT 48000 0.0
006400 삼성SDI 전자 710000 0.0
207940 삼성바이오 바이오 820000 0.0
373220 LG에너지솔루션 전자 420000 0.0
000270 기아 자동차 82000 0.0
EOL
```

## Usage

1. 프로그램 실행:
```bash
./stock_simulator
```

2. 기본 기능:
- 회원가입/로그인
- 주식 목록 조회
- 주식 검색
- 매수/매도
- 포트폴리오 관리

3. 데이터 파일:
- `trading_data/users.txt`: 사용자 정보
- `trading_data/stocks.txt`: 주식 정보
- `trading_data/portfolio.txt`: 포트폴리오 정보
- `trading_data/transactions.txt`: 거래 내역

## Inference

### 주식 거래 방법
1. 로그인 후 메인 메뉴에서 "1. 주식 목록" 선택
2. 거래하고자 하는 주식의 이름 입력
3. 매수/매도 선택 후 수량 입력

### 거래 기록 형식
```
사용자ID 종목코드 거래유형 수량 가격 날짜
예: user1 005930 B 10 72000 2024-12-14
```
- 거래유형: B(매수), S(매도)

### 자동 업데이트
- 주가는 1분마다 자동으로 -5%에서 +5% 범위 내에서 변동
- 모든 거래 내역과 포트폴리오 정보는 실시간으로 파일에 저장

## References

- C언어 Express 개정 4판
- SW융합코딩2 8-9주차 강의자료 05-입출력.pdf

### 프로젝트 구조
```
stock_simulator/
├── main.c
├── user_system.c
├── user_system.h
├── stock_system.c
├── stock_system.h
├── portfolio_system.c
├── portfolio_system.h
└── trading_data/
    ├── users.txt
    ├── stocks.txt
    ├── portfolio.txt
    └── transactions.txt
```

### 개발자 정보
- SW융합대학 모바일시스템공학과 조민형
- SW융합대학 컴퓨터공학과 신철민
- SW융합대학 모바일시스템공학과 정승아

---
