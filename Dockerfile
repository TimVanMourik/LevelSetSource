FROM ubuntu:xenial-20161213

RUN mkdir /code /code/requirements
WORKDIR /code

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        # for creating C++ build environment
        build-essential \
        # for creating Qt build environment
        qtbase5-dev

ADD . /code


RUN cd /code/Qt \
    && qmake -qt=qt5 LevelsetToMesh.pro \
    && make \
    && apt-get purge -yq build-essential \
    && apt-get -yq autoremove \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
