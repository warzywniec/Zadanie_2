# Stage 1: Compiling the Server.c file using alpine Image
FROM alpine:latest AS builder

RUN apk add --no-cache build-base curl

COPY server.c /src/
WORKDIR /src
RUN gcc -Os -static -o server server.c

# Stage 2: Final Image
FROM scratch
# OCI Label
LABEL org.opencontainers.image.authors="Wawrzyniec Lukasiewicz"

COPY --from=builder /src/server /server

# Copy curl binary from builder stage for use in HEALTHCHECK since there is no shell in scratch
COPY --from=builder /usr/bin/curl /curl

# HEALTHCHECK
HEALTHCHECK --interval=10s --timeout=1s CMD ["/curl", "-f", "http://localhost:8080"] || exit 1

EXPOSE 8080

ENTRYPOINT ["/server"]
