FROM ubuntu:jammy

WORKDIR /workspaces/moneymanagerex

# Avoid warnings by switching to noninteractive
ENV DEBIAN_FRONTEND=noninteractive

# Install required packages
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    build-essential \
    libssl-dev \
    gettext \
    git \
    pkg-config \
    lsb-release \
    file \
    ccache \
    libgtk-3-dev \
    liblua5.3-dev \
    libcurl4-openssl-dev \
    libwebkit2gtk-4.0-dev \
    wget \
    unzip \
    python3 \
    appstream \
    libsqlite3-dev \
    libwayland-dev \
    wayland-protocols \
    libxkbcommon-dev \
    xauth \
    && rm -rf /var/lib/apt/lists/*

# Install wxWidgets
RUN cd / \
    && wget --no-check-certificate https://github.com/wxWidgets/wxWidgets/releases/download/v3.1.7/wxWidgets-3.1.7.zip \
    && unzip -d wxWidgets wxWidgets-*.zip \
    && rm wxWidgets-*.zip \
    && cd wxWidgets \
    && mkdir build-linux \
    && cd build-linux \
    && ../configure --disable-shared --enable-cxx11 --with-cxx=11 --enable-webview --with-gtk=3 --enable-unicode --enable-intl \
    && make -j$(nproc) \
    && make install \
    && ldconfig

# Switch back to dialog for any ad-hoc use of apt-get
ENV DEBIAN_FRONTEND=dialog

# Create the user and group
RUN groupadd --gid 1000 vscode \
    && useradd --uid 1000 --gid 1000 -m vscode

# Set the default user for the container
USER vscode
