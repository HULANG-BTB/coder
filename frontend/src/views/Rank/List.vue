<template>
  <el-container>
    <el-header :style="{height: 'initial'}">
      <el-row style="text-align: center;">
        <el-row>
          <h1>排行</h1>
          <el-input placeholder="请输入用户名" v-model="keyword" class="input-with-select">
            <el-button slot="append" icon="el-icon-search" @click="search"></el-button>
          </el-input>
        </el-row>
      </el-row>
    </el-header>
    <el-main>
      <el-table
        :data="tableData"
        style="width: 100%"
        border
        fit
      >
        <el-table-column
          label="排名"
          width="100">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.id }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="用户ID"
          width="100">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.id }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="用户名"
        >
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.username }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="正确"
          width="80">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.solved }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="提交"
          width="80">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.submit }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="比例"
          width="140">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.accepted/scope.row.submit }}</span>
          </template>
        </el-table-column>
      </el-table>
    </el-main>
    <el-footer>
      <el-pagination
        @size-change="handleSizeChange"
        @current-change="handlePageChange"
        :current-page="page"
        :page-sizes="[10, 20, 50, 100]"
        :page-size="limit"
        layout="total, sizes, prev, pager, next, jumper"
        :total="total">
      </el-pagination>
    </el-footer>
  </el-container>
</template>

<script>
import {mapActions, mapState} from 'vuex'

export default {
  data () {
    return {
      page: parseInt(this.$route.query.page) || 1,
      limit: parseInt(this.$route.query.limit) || 10,
      keyword: this.$route.query.keyword || ''
    }
  },
  computed: {
    tableData () {
      return this.rankList.data
    },
    ...mapState(['rankList']),
    total () {
      return this.rankList.total
    }
  },
  mounted () {
    const query = this.buildQuery()
    this.getRankList(query)
  },
  methods: {
    ...mapActions(['getRankList']),
    handlePageChange (data) {
      this.page = data
      const query = this.buildQuery()
      this.$router.push({name: 'RankList', query: query})
      this.getRankList(query)
    },
    handleSizeChange (data) {
      this.limit = data
      const query = this.buildQuery()
      this.$router.push({name: 'RankList', query: query})
      this.getRankList(query)
    },
    search () {
      if (this.type !== '') {
        this.page = 1
        const query = this.buildQuery()
        this.$router.push({name: 'RankList', query: query})
        this.getRankList(query)
      }
    },
    buildQuery () {
      return {
        page: this.page,
        limit: this.limit,
        type: this.type,
        keyword: this.keyword
      }
    }
  }
}
</script>

<style scoped>
.el-select {
  width: 150px;
}
</style>
