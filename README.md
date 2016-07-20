# ExLearn

[![Build Status](https://travis-ci.org/sdwolf/exlearn.svg?branch=master)](https://travis-ci.org/sdwolf/exlearn)
[![Coverage Status](https://coveralls.io/repos/github/sdwolf/exlearn/badge.svg?branch=master)](https://coveralls.io/github/sdwolf/exlearn?branch=master)

Elixir artificial intelligence library. (Extreemly early pre pre alpha!!!)

## Example

```elixir
alias ExLearn.NeuralNetwork, as: NN

structure_parameters = %{
  layers: %{
    input:   %{size: 2},
    hidden: [%{activity: :logistic, name: "First Hidden", size: 2}],
    output:  %{activity: :tanh,     name: "Output",       size: 1}
  },
  objective: :quadratic,
  random:    %{distribution: :uniform, range: {-1, 1}}
}

network = NN.initialize(structure_parameters)

training_data = [
  {[0, 0], [0]},
  {[0, 1], [0]},
  {[1, 0], [0]},
  {[1, 1], [1]}
]

configuration = %{
  batch_size:     2,
  data_size:      4,
  epochs:         1000,
  dropout:        0.5,
  learning_rate:  0.5,
  regularization: :L2
}

NN.feed(training_data, configuration, network)

ask_data = [[0, 0], [0, 1], [1, 0], [1, 1]]

result = NN.ask(ask_data, network)

IO.inspect result
```

## Usage with Docker

Add the following aliases to `~/.bash_profile` and source it:

```bash
alias docker-here='docker run --rm -it -u `id -u`:`id -g` -v "$PWD":/work -w /work'
alias docker-root-here='docker run --rm -it -v "$PWD":/work -w /work'
```

## Jupyter Notebook

1. Build the notebook container
    ```bash
    docker build                        \
      -t exlearn-jupyter                \
      --build-arg HOST_USER_UID=`id -u` \
      --build-arg HOST_USER_GID=`id -g` \
      -f docker/notebook/Dockerfile     \
      "$PWD"

    # OR the short version if you are user 1000:1000

    docker build -t exlearn-jupyter -f docker/notebook/Dockerfile "$PWD"
    ```

2. Run the server
    ```bash
    docker-here -p 8888:8888 exlearn-jupyter
    ```

## Development

2. Build the project container
    ```bash
    docker build                        \
      -t exlearn                        \
      --build-arg HOST_USER_UID=`id -u` \
      --build-arg HOST_USER_GID=`id -g` \
      -f docker/project/Dockerfile      \
      "$PWD"

    # OR the short version if you are user 1000:1000

    docker build -t exlearn -f docker/project/Dockerfile "$PWD"
    ```

3. Update dependencies
    ```bash
    docker-here exlearn mix deps.get
    ```

4. Run an interactive shell
    ```bash
    docker-here exlearn iex -S mix
    ```

5. Run a sample
    ```bash
    docker-here exlearn mix run samples/or.exs
    ```

6. Run tests
    ```bash
    docker-here exlearn mix test
    ```

7. Run tests with coverage report
    ```bash
    docker-here exlearn mix coveralls
    ```

8. Run dialyzer
    ```bash
    docker-here exlearn mix dialyzer
    ```

## LICENSE

This plugin is covered by the BSD license, see [LICENSE](LICENSE) for details.
