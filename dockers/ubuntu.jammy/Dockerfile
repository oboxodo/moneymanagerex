FROM ubuntu:jammy
MAINTAINER developers@moneymanagerex.org

RUN apt-get update && apt-get install -y \
    sudo \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

ARG USERNAME=vscode
ARG USER_UID=1000
RUN useradd -m -s /bin/bash -u ${USER_UID} ${USERNAME} \
    && echo ${USERNAME} ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/${USERNAME} \
    && chmod 0440 /etc/sudoers.d/${USERNAME}

RUN ln -snf /usr/share/zoneinfo/Europe/London /etc/localtime && echo "Europe/London" > /etc/timezone && \
    apt update && \
    apt install -y --no-install-recommends \
      cmake build-essential libssl-dev gettext git pkg-config lsb-release file ccache \
      libgtk-3-dev liblua5.3-dev libcurl4-openssl-dev libwebkit2gtk-4.0-dev wget unzip && \
    apt clean && \
    cd / && \
    wget --no-check-certificate https://github.com/wxWidgets/wxWidgets/releases/download/v3.1.7/wxWidgets-3.1.7.zip && \
    unzip -d wxWidgets wxWidgets-*.zip && \
    rm wxWidgets-*.zip && \
    cd wxWidgets && \
    mkdir build-linux && \
    cd build-linux && \
    ../configure --disable-shared --enable-cxx11 --with-cxx=11 --enable-webview --with-gtk=3 --enable-unicode --enable-intl && \
    make

ENV MMEX_INST_CMD apt install -yqV ./mmex_*.deb
