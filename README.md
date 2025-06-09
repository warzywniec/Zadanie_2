# Zadanie 2

Opracowany łańcuch: ".github/workflows/gha.yml"

### Wsparcie dla architektur: linux/arm64 oraz linux/amd64

```YAML
platforms: linux/amd64,linux/arm64
```

### Dane cache

są przechowywane w publicznym repozytorium na dockerhubie: [cache](https://hub.docker.com/repository/docker/wawrzyniec/zad2-cache/general)

Nazwa repozytorium do przechowywania cache jest podana jako env:

```YAML
env:
  CACHE_REPO: ${{ vars.DOCKERHUB_USERNAME }}/zad2-cache
```

Zapisywanie oraz pobieranie:

```YAML
          cache-from: |
            type=registry,ref=${{ env.CACHE_REPO }}:cache
          cache-to: |
            type=registry,ref=${{ env.CACHE_REPO }}:cache,mode=max
```

### CVE

W celu CVE wykorzytywany jest skaner Trivy v0.63.0

```YAML
      - name: Run Trivy security scan
        uses: aquasecurity/trivy-action@0.31.0
        with:
          image-ref: ${{ env.IMAGE_TAG }}
          format: table
          severity: CRITICAL,HIGH
          exit-code: 1
```
